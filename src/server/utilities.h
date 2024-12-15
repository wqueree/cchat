#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_argv_port(int argc, const char* argv[], int* port) {
    for (size_t i = 0; i < argc - 1; ++i) {
        if (strcmp("-p", argv[i]) == 0) {
            *port = atoi(argv[i + 1]);
            if (*port > 0) {
                return 0;
            }
            if (*port < 1) {
                printf("ERROR: Port number invalid.\n");
                errno = ENOENT;
                return -1;
            }
        }
    }
    printf("ERROR: Port number not supplied.\n");
    errno = ENOENT;
    return -1;
}

int get_argv_max_clients(int argc, const char* argv[], int* max_clients) {
    for (size_t i = 0; i < argc - 1; ++i) {
        if (strcmp("-m", argv[i]) == 0) {
            *max_clients = atoi(argv[i + 1]);
            if (*max_clients >= 0) {
                return 0;
            }
            if (*max_clients < 1) {
                printf("ERROR: Max clients must be >0.\n");
                errno = ENOENT;
                return -1;
            }
        }
    }
    printf("ERROR: Max Clients not supplied.\n");
    errno = ENOENT;
    return -1;
}

