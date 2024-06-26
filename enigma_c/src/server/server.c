#include <cjson/cJSON.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../enigma/enigma.h"
#include "../helper/helper.h"
#include "json_request_parser/json_request_parser.h"

#define PORT 17576
#define THREAD_NUM 10
#define CONNECTION_NUM 10

#define HTTP_OK_HEADER "HTTP/1.1 200 OK\r\n"

char *build_response(char *traversed_text)
{
    // create response in json
    cJSON *response_json = cJSON_CreateObject();
    cJSON_AddStringToObject(response_json, "traversed_text", traversed_text);
    char *response_json_string = cJSON_Print(response_json);
    cJSON_Delete(response_json);

    // create response in http
    char *response = malloc(2048);
    sprintf(response, "%s", HTTP_OK_HEADER);
    sprintf(response + strlen(response),
            "Content-Type: application/json\r\n"
            "Content-Length: %ld\r\n"
            "Connection: close\r\n"
            "Origin: *\r\n"
            "Access-Control-Allow-Origin: *\r\n",
            strlen(response_json_string));
    sprintf(response + strlen(response), "\r\n");
    sprintf(response + strlen(response), "%s", response_json_string);

    free(response_json_string);

    return response;
}

char *build_error_response(void)
{
    char *response = malloc(2048);
    sprintf(response, "HTTP/1.1 400 Bad Request\r\n");
    sprintf(response + strlen(response), "Content-Type: text/plain\r\n"
                                         "Content-Length: 0\r\n"
                                         "Connection: close\r\n"
                                         "Origin: *\r\n"
                                         "Access-Control-Allow-Origin: *\r\n");
    sprintf(response + strlen(response), "\r\n");

    return response;
}

void *handle_client(void *arg)
{
    int client_socket = *(int *)arg;
    char buffer[1024] = {0};

    if (read(client_socket, buffer, 1024) == -1)
    {
        perror("Error reading from socket");
        close(client_socket);

        return NULL;
    }

    char *header_end = strstr(buffer, "\r\n\r\n");

    if (header_end == NULL)
    {
        char *response = build_error_response();
        write(client_socket, response, strlen(response));

        return NULL;
    }

    char *body = header_end + 4;

    EnigmaConfiguration enigma_configuration;

    if (validate_enigma_json(body, &enigma_configuration) == 0)
    {
        char *response = build_error_response();
        write(client_socket, response, strlen(response));

        return NULL;
    }

    Enigma *enigma = create_enigma_from_configuration(&enigma_configuration);
    char *traversed_text = get_string_from_int_array(
        traverse_enigma(enigma), strlen(enigma_configuration.message));

    char *response = build_response(traversed_text);
    write(client_socket, response, strlen(response));

    free(traversed_text);
    free(enigma_configuration.rotors);
    free(enigma_configuration.ring_settings);
    free(enigma_configuration.rotor_positions);
    free(enigma);

    close(client_socket);

    return NULL;
}

int server_run(void)
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket == -1)
    {
        perror("Error creating socket");
        return 1;
    }

    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &(int){1},
                   sizeof(int)) < 0)
    {
        perror("Error setting socket options");
        return 1;
    }

    struct sockaddr_in server_addr = {
        .sin_family      = AF_INET,
        .sin_port        = htons(PORT),
        .sin_addr.s_addr = INADDR_ANY,
    };

    int bind_result = bind(server_socket, (struct sockaddr *)&server_addr,
                           sizeof(server_addr));

    if (bind_result == -1)
    {
        perror("Error binding socket");
        return 1;
    }

    int listen_result = listen(server_socket, CONNECTION_NUM);

    if (listen_result == -1)
    {
        perror("Error listening on socket");
        return 1;
    }

    pthread_t thread[THREAD_NUM];

    while (1)
    {
        unsigned int addr_len = sizeof(struct sockaddr_in);
        int new_socket        = accept(server_socket, NULL, &addr_len);

        if (new_socket == -1)
        {
            perror("Error accepting connection");
            return 1;
        }

        int i = 0;

        int thread_result =
            pthread_create(&thread[i++], NULL, handle_client, &new_socket);

        if (thread_result != 0)
        {
            perror("Error creating thread");
            return 1;
        }

        if (i >= THREAD_NUM)
        {
            i = 0;

            for (int j = 0; j < THREAD_NUM; j++)
            {
                pthread_join(thread[j], NULL);
            }

            i = 0;
        }
    }

    return 0;
}
