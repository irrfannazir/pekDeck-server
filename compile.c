#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

int main() {
    printf("Compiling the program...\n");

    #ifdef _WIN32
        int status = system("gcc server.c slib.c -o pekServer -lws2_32");
    #else
        int status = system("gcc server.c slib.c -o pekServer");
    #endif

    if (status == -1) {
        printf("Error: Could not compile server.\n");
    } else {
        printf("\nCompiled the server: %d\n", status);
    }


    #ifdef _WIN32
        status = system("gcc client.c clib.c -o pekDeck -lws2_32");
    #else
        status = system("gcc client.c clib.c -o pekDeck");
    #endif

    if (status == -1) {
        printf("Error: Could not compile slient.\n");
    } else {
        printf("\nCompiled the client: %d\n", status);
    }

    #ifdef _WIN32
        Sleep(3000);
    #else
        sleep(3);
    #endif

    return 0;
}