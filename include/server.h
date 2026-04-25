#include "neth.h"

#define PORT 8080
#define BUFFER_SIZE 1024

int set_reuseaddr(socket_t sock);
int bind_socket(socket_t sock, int port);
int start_listening(socket_t sock, int backlog);
socket_t accept_client(socket_t server_sock, struct sockaddr_in *client_addr);
void handle_client(socket_t client_sock, struct sockaddr_in *client_addr);
int receive_message(socket_t sock, char *buffer, size_t buf_size);
int send_message(socket_t sock, const char *msg);
