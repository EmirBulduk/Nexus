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
#define TCP 8080
#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

void handleClient(int serverSocket, int clientSocket);

int com() {
    printf("Communications Starting\n");
}

int cnc() {
    printf("cnc services starting\n");
}

int con() {
    printf("TELNET PORT : %d\n", PORT);
    return 0;
}

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

    printf("Nexus Net Starting ... \n");
    con();
    com();
    cnc();

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

    typedef struct {
        char username[20];
        char password[20];
    } User;

    // Send a welcome message to the client
    const char* welcomeMsg = "Nexus\r\n";
    send(clientSocket, welcomeMsg, strlen(welcomeMsg), 0);

    // Assuming MAX_USERS is the maximum number of users your system can handle
    #define MAX_USERS 10
    User users[MAX_USERS] = {
        {"admin", "admin"}
        // Add more users as needed
    };

    // Send a prompt for the username
    const char* usernamePrompt = "user: ";
    send(clientSocket, usernamePrompt, strlen(usernamePrompt), 0);

    // Receive the username from the client
    bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    buffer[bytesRead] = '\0'; // Null-terminate the received data

    // Check if the username is valid
    char username[20];
    strcpy(username, buffer);

    // Send a prompt for the password
    const char* passwordPrompt = "password: ";
    send(clientSocket, passwordPrompt, strlen(passwordPrompt), 0);

    // Receive the password from the client
    bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    buffer[bytesRead] = '\0'; // Null-terminate the received data

    // Check if the password is valid
    char password[20];
    strcpy(password, buffer);


    printf("Received username: %s\n", username);
    printf("Received password: %s\n", password);

    int isValidUser = 0;
    for (int i = 0; i < MAX_USERS; i++) {
        printf("Comparing with user: %s, password: %s\n", users[i].username, users[i].password);
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            isValidUser = 1;
            break;
        }
    }

    if (isValidUser) {
        while (1) {
            char* banner =
                "███╗   ██╗███████╗██╗  ██╗██╗   ██╗███████╗\r\n"
                "████╗  ██║██╔════╝╚██╗██╔╝██║   ██║██╔════╝\r\n"
                "██╔██╗ ██║█████╗   ╚███╔╝ ██║   ██║███████╗\r\n"
                "██║╚██╗██║██╔══╝   ██╔██╗ ██║   ██║╚════██║\r\n"
                "██║ ╚████║███████╗██╔╝ ██╗╚██████╔╝███████║\r\n"
                "╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝\r\n"
                "      --**Welcome To Nexus Network**--- \r\n";

            send(clientSocket, banner, strlen(banner), 0);

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
            }
        }
    } else {
        // Invalid credentials, you can send a message to the client and handle it accordingly.
        const char* errorMsg = "Invalid username or password. Please try again.\r\n";
        send(clientSocket, errorMsg, strlen(errorMsg), 0);
        // Optionally, you can close the connection or implement other actions.
    }
}
