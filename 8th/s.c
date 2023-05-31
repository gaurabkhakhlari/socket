#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int main() {
    int sockfd, newsockfd, clientlen, n;
    struct sockaddr_in serv_addr, cli_addr;
    char buffer[256];

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(1);
    }

    // Clear address structure
    memset((char *)&serv_addr, 0, sizeof(serv_addr));

    // Set up server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    // Bind socket to the specified address and port
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error binding");
        exit(1);
    }

    // Listen for connections
    listen(sockfd, 5);
    printf("Server listening on port %d...\n", PORT);

    // Accept incoming connection
    clientlen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clientlen);
    if (newsockfd < 0) {
        perror("Error accepting connection");
        exit(1);
    }

    // Receive message from client
    bzero(buffer, 256);
    n = read(newsockfd, buffer, 255);
    if (n < 0) {
        perror("Error reading from socket");
        exit(1);
    }

    printf("Received message from client: %s\n", buffer);

    // Send acknowledgement to client
    char ack[] = "Message received";
    n = write(newsockfd, ack, strlen(ack));
    if (n < 0) {
        perror("Error writing to socket");
        exit(1);
    }

    // Receive number from client
    bzero(buffer, 256);
    n = read(newsockfd, buffer, 255);
    if (n < 0) {
        perror("Error reading from socket");
        exit(1);
    }

    int num = atoi(buffer);

    // Display message for n times
    for (int i = 0; i < num; i++) {
        printf("Message from client: %s\n", buffer);
    }

    // Close sockets
    close(newsockfd);
    close(sockfd);

    return 0;
}

