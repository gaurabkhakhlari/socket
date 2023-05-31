#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 8080

int main() {
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(1);
    }

    // Get server address
    server = gethostbyname("localhost");
    if (server == NULL) {
        perror("Error, no such host");
        exit(1);
    }

    // Clear address structure
    memset((char *)&serv_addr, 0, sizeof(serv_addr));

    // Set up server address
    serv_addr.sin_family = AF_INET;
    memcpy((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
    serv_addr.sin_port = htons(PORT);

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error connecting");
        exit(1);
    }

    // Send message to server
    char message[] = "Hello, server!";
    n = write(sockfd, message, strlen(message));
    if (n < 0) {
        perror("Error writing to socket");
        exit(1);
    }

    // Receive acknowledgement from server
    bzero(buffer, 256);
    n = read(sockfd, buffer, 255);
    if (n < 0) {
        perror("Error reading from socket");
        exit(1);
    }

    printf("Server: %s\n", buffer);

    // Send number to server
    int num = 5;
    sprintf(buffer, "%d", num);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0) {
        perror("Error writing to socket");
        exit(1);
    }

    // Close socket
    close(sockfd);

    return 0;
}

