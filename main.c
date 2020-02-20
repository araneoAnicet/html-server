#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#define DEFAULT_PORT 80


FILE* getHTMLDocument(char* fileName) {
    return fopen(fileName, "r");
}

struct sockaddr_in generate_socket_structure(
    short address_family,
    unsigned short port,
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
        printf("Binding socket...\n");
        bind(socket_file_descriptor, (struct sockaddr*) &socket_info, sizeof(socket_info));
        printf("New socket binded at %u:%d\n", socket_info.sin_addr.s_addr, socket_info.sin_port);
        return socket_file_descriptor;
    } else {
        printf("FAILED SOCKET CREATING\n");
    }
}

void run(int socket_file_descriptor, int max_requests, char* responseHeader, int sizeOfResponseHeaders,  FILE* htmlDocument) {
    int listening = listen(socket_file_descriptor, max_requests);
    if (listening == 0) {
        printf("Listening %d connections on socket...\n", max_requests);
        int client_socket_file_descriptor;
        short receive_buffer_size = 8192;
        char receive_buffer[receive_buffer_size];
        while (1) {
            client_socket_file_descriptor = accept(socket_file_descriptor, NULL, NULL);
            printf("ACCEPTED NEW CONNECTION!\n");
            int received_bytes = read(client_socket_file_descriptor, receive_buffer, receive_buffer_size);

            printf("Received data:\n%s", receive_buffer);


            int responseSize;
            char* buffer;
            long fileSize;
            fseek(htmlDocument, 0, SEEK_END);
            fileSize = ftell(htmlDocument);
            fseek(htmlDocument, 0, SEEK_SET);
            buffer = malloc(fileSize);
            fread(buffer, 1, fileSize, htmlDocument);
            responseSize = sizeOfResponseHeaders + sizeof(const char) * 2 + fileSize;
            printf("RESPONSE SIEZE: %li BYTES\n", responseSize);
            char response[responseSize];

            strcpy(response, responseHeader);
            strcat(response, "\n\n");
            strcat(response, buffer);

            printf("SENDING RESPONSE......\n%s", response);

            free(buffer);
            fclose(htmlDocument);
            send(client_socket_file_descriptor, response, responseSize, 0);
            close(client_socket_file_descriptor);
            printf("CONNECTION CLOSED!\n");
           
        }
    } else {
        printf("FAILED SOCKET LISTENING\n");
    }

}

int main() {
    int sizeOfResponseHeaders = sizeof(const char) * 57;
    struct sockaddr_in socket_info = generate_socket_structure(AF_INET, DEFAULT_PORT, "127.0.0.1");
    int socket_file_descriptor = create_socket(socket_info, SOCK_STREAM);
    
    run(
        socket_file_descriptor,
        1,
        "HTTP/1.1 200 OK\n Content-Type: text/html; charset=utf-8\n\n",
        sizeOfResponseHeaders,
        getHTMLDocument("test.html")
    );
    //close(socket_file_descriptor);
    return 0;
}