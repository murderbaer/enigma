#include "server.h"

#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 17576
#define OK_RESPONSE "HTTP/1.1 200 OK\r\n\r\n"

int server_run(void)
{
    int _socket = socket(AF_INET, SOCK_STREAM, 0);

    if (_socket < 0)
    {
        perror("Could not create socket\n");
    }

    setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));

    struct sockaddr_in server = {0};
    server.sin_family         = AF_INET;
    server.sin_port           = htons(PORT);
    server.sin_addr.s_addr    = INADDR_ANY;
    memset(server.sin_zero, '\0', 8);

    if (bind(_socket, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Could not bind socket\n");
    }

    if (listen(_socket, 10) < 0)
    {
        perror("Could not listen on socket\n");
    }

    printf("Listening on port %d\n", PORT);

    // TODO: Add signal handlers
    // TODO: Add thread pool
    // TODO: Add request handler
    // TODO: Add response handler
    // TODO: Add logging
    while (1)
    {
        struct sockaddr_in client = {0};
        socklen_t client_len      = sizeof(client);
        int client_socket =
            accept(_socket, (struct sockaddr *)&client, &client_len);

        if (client_socket < 0)
        {
            perror("Could not establish new connection\n");
        }

        char buffer[1024] = {0};
        read(client_socket, buffer, 1024);

        char *response = "HTTP/1.1 200 OK\r\n\r\nHello, World!\r\n";

        write(client_socket, response, strlen(response));
        close(client_socket);
    }

    return 0;
}
