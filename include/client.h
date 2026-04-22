#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    typedef SOCKET socket_t;
    #define CLOSE_SOCKET(s) closesocket(s)
    #define SOCKET_ERROR_CODE WSAGetLastError()
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <errno.h>
    typedef int socket_t;
    #define CLOSE_SOCKET(s) close(s)
    #define SOCKET_ERROR_CODE errno
#endif

#define SERVER_IP   "127.0.0.1"
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024


int network_init(void);
void network_cleanup(void);
socket_t create_socket(void);
int connect_to_server(socket_t sock, const char *ip, int port);
void close_socket(socket_t sock);
int send_message(socket_t sock, const char *msg);
int receive_message(socket_t sock, char *buffer, size_t buf_size);
void run_chat_loop(socket_t sock);