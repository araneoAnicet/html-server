#include "Server.h"


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
    close(socket_file_descriptor);
    return 0;
}
