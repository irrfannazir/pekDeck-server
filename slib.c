#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/server.h"



//for faster restart after crash
int set_reuseaddr(socket_t sock) {
    int opt = 1;
#ifdef _WIN32
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(opt)) < 0) {
#else
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
#endif
        perror("setsockopt(SO_REUSEADDR) failed");
        return -1;
    }
    return 0;
}

int bind_socket(socket_t sock, int port) {
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        fprintf(stderr, "Bind failed, error code: %d\n", SOCKET_ERROR_CODE);
        return -1;
    }
    return 0;
}

//Start listening for incoming connections with the specified backlog
int start_listening(socket_t sock, int backlog) {
    if (listen(sock, backlog) < 0) {
        perror("Listen failed");
        return -1;
    }
    return 0;
}

// Accept a new client connection and return its socket.
socket_t accept_client(socket_t server_sock, struct sockaddr_in *client_addr) {
    socklen_t client_len = sizeof(*client_addr);
    socket_t client_fd = accept(server_sock, (struct sockaddr *)client_addr, &client_len);
    if (client_fd < 0) {
        perror("Accept failed");
    }
    return client_fd;
}

// handles communication with a single client.
// receives messages and sends back an acknowledgment.
 void handle_client(socket_t client_sock, struct sockaddr_in *client_addr) {
    char buffer[BUFFER_SIZE];

    printf("Client connected: %s:%d\n",
           inet_ntoa(client_addr->sin_addr),
           ntohs(client_addr->sin_port));

    while (1) {
        /* Receive message from client */
        int bytes = receive_message(client_sock, buffer, BUFFER_SIZE);
        if (bytes <= 0) {
            printf("Client disconnected\n");
            break;
        }

        printf("Received: %s\n", buffer);

        /* Send acknowledgment */
        const char *response = "Message received by server";
        if (send_message(client_sock, response) != 0) {
            printf("Failed to send response, closing connection\n");
            break;
        }
    }
}

// returns number of bytes received, 0 if connection closed, -1 on error
int receive_message(socket_t sock, char *buffer, size_t buf_size) {
#ifdef _WIN32
    int bytes = recv(sock, buffer, (int)(buf_size - 1), 0);
#else
    ssize_t bytes = recv(sock, buffer, buf_size - 1, 0);
#endif
    if (bytes > 0) {
        buffer[bytes] = '\0';
    } else if (bytes == 0) {
        // connection closed gracefully
        ;
    } else {
        perror("Receive failed");
    }
    return (int)bytes;
}

int send_message(socket_t sock, const char *msg) {
    if (send(sock, msg, (int)strlen(msg), 0) < 0) {
        perror("Send failed");
        return -1;
    }
    return 0;
}