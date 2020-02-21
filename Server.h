#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#define DEFAULT_PORT 80

FILE* getHTMLDocument(char* fileName);

struct sockaddr_in generate_socket_structure(
    short address_family,
    unsigned short port,
    const char* network_address
    );

int create_socket(struct sockaddr_in socket_info, int protocol_index);

void run(
    int socket_file_descriptor,
    int max_requests,
    char* responseHeader,
    int sizeOfResponseHeaders,
    FILE* htmlDocument
    );

