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

int get_argv_address(int argc, const char* argv[], struct in_addr* address) {
    for (size_t i = 0; i < argc - 1; ++i) {
        if (strcmp("-a", argv[i]) == 0) {
            int inet_pton_ret = inet_pton(AF_INET, argv[i + 1], address);
            if (inet_pton_ret == 1) {
                return 0;
            }
            if (inet_pton_ret == 0) {
                printf("ERROR: Address string invalid.\n");
                errno = ENOENT;
                return -1;
            }
            if (inet_pton_ret == -1) {
                printf("ERROR: Address family AF_INET invalid.\n");
                errno = EAFNOSUPPORT;
                return -1;
            }
        }
    }
    printf("ERROR: Address string not supplied.\n");
    errno = ENOENT;
    return -1;
}

void get_name(char* buf, size_t n) {
    int halfn = n / 2;
    char* first_name_buf = (char*) malloc(halfn * sizeof(char));
    char* last_name_buf = (char*) malloc(halfn * sizeof(char));
    printf("First Name: ");
    fgets(first_name_buf, halfn, stdin);
    first_name_buf[strcspn(first_name_buf, "\n")] = '\0';
    printf("Last Name: ");
    fgets(last_name_buf, halfn, stdin);
    last_name_buf[strcspn(last_name_buf, "\n")] = '\0';
    snprintf(buf, n, "%s %s", first_name_buf, last_name_buf);
    free(first_name_buf);
    free(last_name_buf);
}