//Program to Retrieve Webpage using SSL TLS in C by kelvin gathuru
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

int main()
{
    char url[256];
    printf("Enter the URL of the webpage you want to retrieve: ");
    fgets(url, sizeof(url), stdin);
    url[strcspn(url, "\n")] = 0;  // Remove trailing newline

    // Extract the hostname and path from the URL
    char* host = strtok(url, "/");
    char* path = strtok(NULL, "");

    // Create a TCP/IP socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    // Resolve the hostname to an IP address
    struct hostent* he = gethostbyname(host);
    if (he == NULL) {
        herror("gethostbyname");
        exit(1);
    }

    // Connect to the server
    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(443)  // HTTPS uses port 443
    };
    memcpy(&server_addr.sin_addr.s_addr, he->h_addr, he->h_length);
    if (connect(sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        exit(1);
    }

    // Wrap the socket with SSL/TLS
    SSL_library_init();
    SSL_CTX* ssl_ctx = SSL_CTX_new(TLS_client_method());
    SSL* ssl = SSL_new(ssl_ctx);
    SSL_set_fd(ssl, sock);
    if (SSL_connect(ssl) != 1) {
        ERR_print_errors_fp(stderr);
        exit(1);
    }

    // Send the HTTP GET request
    char request[512];
    snprintf(request, sizeof(request), "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", path, host);
    if (SSL_write(ssl, request, strlen(request)) <= 0) {
        perror("SSL_write");
        exit(1);
    }

    // Receive the response
    char response[4096];
    int n;
    while ((n = SSL_read(ssl, response, sizeof(response) - 1)) > 0) {
        response[n] = '\0';
        printf("%s", response);
    }
    if (n < 0) {
        perror("SSL_read");
        exit(1);
    }

    // Clean up
    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ssl_ctx);
    close(sock);

    return 0;
}
