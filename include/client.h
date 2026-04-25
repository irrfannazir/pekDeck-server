#include "neth.h"

#define SERVER_IP   "127.0.0.1"
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024


int connect_to_server(socket_t sock, const char *ip, int port);
int send_message(socket_t sock, const char *msg);
int receive_message(socket_t sock, char *buffer, size_t buf_size);
void run_chat_loop(socket_t sock);