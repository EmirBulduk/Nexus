// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "headers/cman.h"

#define PORT 23
#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

void handleClient(int clientSocket);

int main() {
    // Initialize the command handler
    initializeCommandHandler();

    // Register commands
    registerCommand("help", executeHelpCommand);
    // Register other commands similarly...

    // ... (unchanged code)

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

            // Execute the command using the command handler
            executeCommand(clientSocket, buffer);
        } else {
            // If no newline character is found, continue receiving data
            send(clientSocket, buffer, bytesRead, 0);
        }
    }
}