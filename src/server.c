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

void handleClient(int serverSocket, int clientSocket);

int main() {
    int serverSocket;  // Declare serverSocket before using it

    // Initialize the command handler
    initializeCommandHandler();

    // Register commands
    registerCommand("help", executeHelpCommand);
    registerCommand("echo", executeEchoCommand);
    // Register other commands similarly...

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
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
        handleClient(serverSocket, clientSocket);

        // Close the client socket after handling the connection
        close(clientSocket);

        printf("Client disconnected\n");
    }

    // Cleanup
    close(serverSocket);

    return 0;
}

void handleClient(int serverSocket, int clientSocket) {
    char buffer[BUFFER_SIZE];
    int bytesRead;

    int isvalid = 0;

struct User {
    char username[20];
    char password[20];
};
#define MAX_USERS 10
    struct User users[MAX_USERS] = {
        {"admin", "admin"},

    };

    const char* userprompt = "user: ";
    send(clientSocket, userprompt, strlen(userprompt), 0);



    bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    if (bytesRead <= 0) {
        return;
    }


    buffer[bytesRead] = '\0';

    char username[20];
    strcpy(username, buffer);
    printf("Received username: %s\n", username);

    // Send a prompt for the password
    const char* passwordPrompt = "password: ";
    send(clientSocket, passwordPrompt, strlen(passwordPrompt), 0);

    // Receive the password from the client
    bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);

    if (bytesRead <= 0) {
        // If the client disconnects or an error occurs, return immediately
        return;
    }

    // Process the received data
    buffer[bytesRead] = '\0'; // Null-terminate the received data

    // Now 'buffer' contains the password entered by the client
    char password[20];
    strcpy(password, buffer);
    printf("Received password: %s\n", password);


    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            isValidUser = 1;
            break;
        }
    }
    if(isvalid) {
        printf("Welcome\r\n");
        while (1) {
            // Receive data from the client
            bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);

            if (bytesRead <= 0) {
                break;}
            buffer[bytesRead] = '\0';
            char* newlinePos = strchr(buffer, '\n');
            if (newlinePos != NULL) {*newlinePos = '\0';
                executeCommand(clientSocket, buffer);
            } else {
                send(clientSocket, buffer, bytesRead, 0);
            }
        }
    }
}