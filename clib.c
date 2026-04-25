#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/client.h"

int connect_to_server(socket_t sock, const char *ip, int port) {
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    // Convert IP address to binary form
#ifdef _WIN32
    server_addr.sin_addr.s_addr = inet_addr(ip);
    if (server_addr.sin_addr.s_addr == INADDR_NONE) {
        fprintf(stderr, "Invalid address: %s\n", ip);
        return -1;
    }
#else
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
        fprintf(stderr, "Invalid address: %s\n", ip);
        return -1;
    }
#endif

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        fprintf(stderr, "Connection failed, error code: %d\n", SOCKET_ERROR_CODE);
        return -1;
    }
    return 0;
}


int send_message(socket_t sock, const char *msg) {
    if (send(sock, msg, (int)strlen(msg), 0) < 0) {
        perror("Send failed");
        return -1;
    }
    return 0;
}

int receive_message(socket_t sock, char *buffer, size_t buf_size) {
#ifdef _WIN32
    int bytes = recv(sock, buffer, (int)(buf_size - 1), 0);
#else
    ssize_t bytes = recv(sock, buffer, buf_size - 1, 0);
#endif
    if (bytes > 0) {
        buffer[bytes] = '\0';
    } else if (bytes == 0) {
        printf("Server disconnected\n");
    } else {
        perror("Receive failed");
    }
    return (int)bytes;
}

void run_chat_loop(socket_t sock) {
    char buffer[BUFFER_SIZE];

    while (1) {
        printf("Enter message (type 'exit' to quit): ");
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        // Send the message to the server
        if (send_message(sock, buffer) != 0) {
            break;
        }

        // Wait for the server's response
        int bytes = receive_message(sock, buffer, BUFFER_SIZE);
        if (bytes <= 0) {
            break;   // Connection closed or error
        }

        printf("Server response: %s\n", buffer);
    }
}