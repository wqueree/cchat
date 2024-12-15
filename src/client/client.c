#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>

#include "utilities.h"


void run_client(int argc, const char** argv) {
    int port;
    if (get_argv_port(argc, argv, &port) != 0) exit(errno);


    struct in_addr address;
    if (get_argv_address(argc, argv, &address) != 0) exit(errno);

    char name[64] = {0};
    get_name(name, 64);


    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serveraddress = {
        AF_INET,
        htons(port),
        address
    };
    connect(clientfd, (struct sockaddr*) &serveraddress, sizeof(serveraddress));
    send(clientfd, name, strlen(name), 0);
    while (true) {
        char buf[2048];
        recv(clientfd, buf, 2048, 0);
        printf("%s\n", buf);
    }
}

int main(int argc, const char** argv) {
    run_client(argc, argv);
    return 0;
}
