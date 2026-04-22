#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")

    typedef SOCKET socket_t;
    #define CLOSE_SOCKET(s) closesocket(s)
    #define SOCKET_ERROR_CODE WSAGetLastError()
#else
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <errno.h>

    typedef int socket_t;
    #define CLOSE_SOCKET(s) close(s)
    #define SOCKET_ERROR_CODE errno
#endif

#define PORT 8080
#define BUFFER_SIZE 1024

int network_init(void);
void network_cleanup(void);
socket_t create_socket(void);
int set_reuseaddr(socket_t sock);
int bind_socket(socket_t sock, int port);
int start_listening(socket_t sock, int backlog);
socket_t accept_client(socket_t server_sock, struct sockaddr_in *client_addr);
void handle_client(socket_t client_sock, struct sockaddr_in *client_addr);
void close_socket(socket_t sock);
int receive_message(socket_t sock, char *buffer, size_t buf_size);
int send_message(socket_t sock, const char *msg);
