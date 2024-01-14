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
    if (!header_end)
    {
        sprintf(buffer, "HTTP/1.1 400 Bad Request\r\n");
        write(client_socket, buffer, strlen(buffer));
        close(client_socket);

        return NULL;
    }

    char *body = header_end + 4;

    printf("client connected\n");

    char response[2048];

    EnigmaConfiguration enigma_configuration;

    if (validate_enigma_json(body, &enigma_configuration) == 0)
    {
        sprintf(response, "HTTP/1.1 400 Bad Request\r\n");
        write(client_socket, response, strlen(response));
        close(client_socket);

        return NULL;
    }

    Enigma *enigma = create_enigma_from_configuration(&enigma_configuration);

    char *traversed_text = get_string_from_int_array(
        traverse_enigma(enigma), strlen(enigma_configuration.message));

    // send traversed text but first we need to create a response
    sprintf(response,
            "HTTP/1.1 200 OK\r\nContent-Type: "
            "application/json\r\n\r\n{\"traversedText\":\"%s\"}",
            traversed_text);
    write(client_socket, response, strlen(response));

    close(client_socket);
    return NULL;
}

int server_run()
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
    int i = 0;

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
