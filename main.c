#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>


typedef struct sockaddr_in socket_address;

socket_address generate_socket_structure(
    sa_family_t address_family,
    int port,
    const char* network_address
    ) {
        socket_address socket_info;
        socket_info.sin_family = address_family;
        socket_info.sin_port = htons(port);
        inet_aton(network_address, &socket_info.sin_addr.s_addr);
        return socket_info;
    };

int main() {
    return 0;
}