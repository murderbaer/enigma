#include <cjson/cJSON.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 17576
#define THREAD_NUM 10
#define CONNECTION_NUM 10

int i = 0;

void *handle_client(void *arg)
{
    int client_socket = *(int *)arg;
    char buffer[1024] = {0};

    // Read request
    read(client_socket, buffer, 1024);

    // Simple parsing to find the end of the headers
    char *header_end = strstr(buffer, "\r\n\r\n");
    if (!header_end)
    {
        // Error: malformed request
        close(client_socket);
        return NULL;
    }

    // Extract body (if any)
    char *body = header_end + 4;

    // Prepare response
    char response[2048];

    cJSON *json = cJSON_Parse(body);

    // Send response and i variable
    // write(client_socket, response, strlen(response));

    close(client_socket);
    return NULL;
}

int server_run()
{
    srand(time(NULL));

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket == -1)
    {
        perror("socket");
        return 1;
    }

    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &(int){1},
                   sizeof(int)) < 0)
    {
        perror("setsockopt(SO_REUSEADDR) failed");
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
        perror("bind");
        return 1;
    }

    int listen_result = listen(server_socket, CONNECTION_NUM);

    if (listen_result == -1)
    {
        perror("listen");
        return 1;
    }

    pthread_t thread[THREAD_NUM];

    while (1)
    {
        int addr_len   = sizeof(struct sockaddr_in);
        int new_socket = accept(server_socket, NULL, &addr_len);

        if (new_socket == -1)
        {
            perror("accept");
            return 1;
        }

        int thread_result =
            pthread_create(&thread[i++], NULL, handle_client, &new_socket);

        if (thread_result != 0)
        {
            perror("pthread_create");
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
