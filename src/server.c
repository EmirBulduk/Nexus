// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "commands/cman.h"
#include "commands/echo_command.h"
#include "commands/help_command.h"

#define PORT 23
#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

// Define user credentials
#define USERNAME "admin"
#define PASSWORD "password"

void handleClient(int serverSocket, int clientSocket);

int authenticateUser(int clientSocket) {
    char buffer[BUFFER_SIZE];
    int bytesRead;

    // Ask for username
    const char* usernamePrompt = "Enter username: ";
    send(clientSocket, usernamePrompt, strlen(usernamePrompt), 0);
    bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    if (bytesRead <= 0) {
        return 0; // Error or client disconnect
    }
    buffer[bytesRead] = '\0'; // Null-terminate the received data

    // Check username
    if (strcmp(buffer, USERNAME) != 0) {
        const char* authFailed = "Authentication failed. Disconnecting.\r\n";
        send(clientSocket, authFailed, strlen(authFailed), 0);
        return 0; // Authentication failed
    }

    // Ask for password
    const char* passwordPrompt = "Enter password: ";
    send(clientSocket, passwordPrompt, strlen(passwordPrompt), 0);
    bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    if (bytesRead <= 0) {
        return 0; // Error or client disconnect
    }
    buffer[bytesRead] = '\0'; // Null-terminate the received data

    // Check password
    if (strcmp(buffer, PASSWORD) != 0) {
        const char* authFailed = "Authentication failed. Disconnecting.\r\n";
        send(clientSocket, authFailed, strlen(authFailed), 0);
        return 0; // Authentication failed
    }

    const char* authSuccess = "Authentication successful. Welcome!\r\n";
    send(clientSocket, authSuccess, strlen(authSuccess), 0);

    return 1; // Authentication successful
}

int main() {
    // ... (unchanged code)

    while (1) {
        int clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == -1) {
            perror("Accept failed");
            close(serverSocket);
            exit(EXIT_FAILURE);
        }

        printf("Client connected\n");

        // Authenticate the client
        if (!authenticateUser(clientSocket)) {
            close(clientSocket);
            continue; // Authentication failed, close connection and wait for the next one
        }

        // Handle the authenticated client in a separate function
        handleClient(serverSocket, clientSocket);

        // Close the client socket after handling the connection
        close(clientSocket);

        printf("Client disconnected\n");
    }

    // Cleanup
    close(serverSocket);

    return 0;
}

}