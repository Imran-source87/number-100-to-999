#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // Create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Server address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Replace with the server IP address if necessary
    server_addr.sin_port = htons(8888);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server.\n");

    // Receive the random number from the server
    int random_number;
    if (recv(client_socket, &random_number, sizeof(random_number), 0) == -1) {
        perror("Receive failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    printf("Random number received from server: %d\n", random_number);

    // Close the socket
    close(client_socket);

    return 0;
}
