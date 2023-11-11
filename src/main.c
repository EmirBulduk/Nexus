#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "headers/cman.h"

#define PORT 55
#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

void handleClient(int clientSocket);




int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Bind failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, MAX_CLIENTS) == -1) {
        perror("Listen failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    printf("Telnet server is listening on port %d...\n", PORT);

    while (1) {
        int clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == -1) {
            perror("Accept failed");
            close(serverSocket);
            exit(EXIT_FAILURE);
        }

        printf("Client connected\n");

        // Handle the client in a separate function
        handleClient(clientSocket);

        // Close the client socket after handling the connection
        close(clientSocket);

        printf("Client disconnected\n");
    }

    // Cleanup
    close(serverSocket);

    return 0;
}

void handleClient(int clientSocket) {
    char buffer[BUFFER_SIZE];
    int bytesRead;

    // Send a welcome message to the client
    const char* welcomeMsg = "Welcome to the simple Telnet server!\r\n";
    send(clientSocket, welcomeMsg, strlen(welcomeMsg), 0);

    while (1) {
        // Receive data from the client
        bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);

        if (bytesRead <= 0) {
            // If the client disconnects or an error occurs, break from the loop
            break;
        }

        // Process the received data
        buffer[bytesRead] = '\0'; // Null-terminate the received data

        // Check if the received data contains a newline character
        char* newlinePos = strchr(buffer, '\n');
        if (newlinePos != NULL) {
            // If a newline character is found, treat it as the end of a line
            *newlinePos = '\0'; // Null-terminate at the newline position
            send(clientSocket, buffer, strlen(buffer), 0); // Echo back the line
            printf("Recived Command: %s\n", buffer);

            //şimdi bu gelen komutun var olup olmadığını kontroll edeceğiz



        } else {
            // If no newline character is found, continue receiving data
            send(clientSocket, buffer, bytesRead, 0);
        }


    }

}

void executeCommand(int clientSocket, const char* command) {
    if (strcmp(command, "help") == 0) {
        const char* helpMsg = "Available commands:\r\n"
                              "help - Display this help message\r\n"
                              "echo [message] - Display the provided message\r\n"
                              "quit - Disconnect from the server\r\n";

        send(clientSocket, helpMsg, strlen(helpMsg), 0);
    } else if (strncmp(command, "echo ", 5) == 0) {
                executeHelpCommand(clientSocket);
    } else if (strcmp(command, "quit") == 0) {
       // executeQuitCommand(clientSocket);
        printf("Not defined");
    } else {
        executeEchoCommand(clientSocket);
    }
}
