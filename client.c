#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/client.h"

int main(void) {
    // initialization
    if (network_init() != 0) {
        fprintf(stderr, "Failed to initialize networking\n");
        return 1;
    }

    // Create a TCP socket
    socket_t client_fd = create_socket();
    if (client_fd < 0) {
        network_cleanup();
        return 1;
    }

    if (connect_to_server(client_fd, SERVER_IP, SERVER_PORT) != 0) {
        close_socket(client_fd);
        network_cleanup();
        return 1;
    }

    printf("Connected to server %s:%d\n", SERVER_IP, SERVER_PORT);

    run_chat_loop(client_fd);

    close_socket(client_fd);
    network_cleanup();
    return 0;
}

