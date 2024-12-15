#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdbool.h>

#include "utilities.h"


int run_server(int argc, const char** argv) {
    int port;
    if (get_argv_port(argc, argv, &port) != 0) exit(errno);

    int max_clients;
    if (get_argv_max_clients(argc, argv, &max_clients) != 0) exit(errno);

    int clients[max_clients];
    int current_clients = 0;

    int serverfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serveraddress = {
        AF_INET,
        htons(port),
        INADDR_ANY
    };

    bind(serverfd, (struct sockaddr*) &serveraddress, sizeof(serveraddress));
    printf("Listening on 127.0.0.1:%d\n", port);
    listen(serverfd, 128);
    while (true)
    {
        struct sockaddr clientaddr;
        int clientfd = accept(serverfd, 0, 0);
        char name[64];
        recv(clientfd, name, 64, 0);
        char join_message[128];
        snprintf(join_message, 128, "%s joined the chat.\n", name);
        for (size_t i = 0; i < current_clients; ++i) {
            int messageclientfd = clients[i];
            printf("%s\n", join_message);
            send(clients[i], join_message, 128, 0);
            clients[current_clients++] = clientfd;
        }
    }
    return 0;
}

int main(int argc, const char** argv) {
    run_server(argc, argv);
    return 0;
}