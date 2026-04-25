#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

int main(void) {
    // initialize
    if (network_init() != 0) {
        fprintf(stderr, "Failed to initialize networking\n");
        return 1;
    }

    socket_t server_fd = create_socket();
    if (server_fd < 0) {
        network_cleanup();
        return 1;
    }

    // allow address reuse to avoid "Address already in use" errors
    if (set_reuseaddr(server_fd) != 0) {
        close_socket(server_fd);
        network_cleanup();
        return 1;
    }

    if (bind_socket(server_fd, PORT) != 0) {
        close_socket(server_fd);
        network_cleanup();
        return 1;
    }

    if (start_listening(server_fd, 5) != 0) {
        close_socket(server_fd);
        network_cleanup();
        return 1;
    }

    printf("Server listening on port %d...\n", PORT);

    // Main accept loop
    while (1) {
        struct sockaddr_in client_addr;
        socket_t client_fd = accept_client(server_fd, &client_addr);
        if (client_fd < 0) {
            continue;   // Accept failed, but server keeps running
        }

        handle_client(client_fd, &client_addr);

        close_socket(client_fd);
    }

    /* This point is never reached in the current design,
       but we keep cleanup for completeness */
    close_socket(server_fd);
    network_cleanup();
    return 0;
}

