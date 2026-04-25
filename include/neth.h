#ifndef NETH_H
#define NETH_H

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

// initialization
static inline int network_init(void) {
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed\n");
        return -1;
    }
#endif
    return 0;
}

static inline void network_cleanup(void) {
#ifdef _WIN32
    WSACleanup();
#endif
}

static inline socket_t create_socket(void) {
    socket_t sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
    }
    return sock;
}

static inline void close_socket(socket_t sock) {
    if (sock >= 0) {
        CLOSE_SOCKET(sock);
    }
}

#endif