#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#define DEFAULT_PORT 80


struct sockaddr_in generate_socket_structure(
    sa_family_t address_family,
    int port,
    const char* network_address
    ) {
        struct sockaddr_in socket_info;
        socket_info.sin_family = address_family;
        socket_info.sin_port = htons(port);
        inet_aton(network_address, &socket_info.sin_addr.s_addr);
        return socket_info;
    };

int create_socket(struct sockaddr_in socket_info, int protocol_index) {
    int socket_file_descriptor = socket(socket_info.sin_family, protocol_index, 0);
    if (socket_file_descriptor != -1) {
        printf("Binding socket...");
        bind(socket_file_descriptor, (struct sockaddr*) &socket_info, sizeof(socket_info));
        printf("New socket binded at %s:%d", socket_info.sin_addr.s_addr, socket_info.sin_port);
        return socket_file_descriptor;
    } else {
        printf("FAILED SOCKET CREATING\n");
        return NULL;
    }
}

int main() {
    return 0;
}