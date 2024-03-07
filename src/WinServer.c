#include <stddef.h>
#include <string.h>

#include "commands/cman.h"
userPrompt), 0);

    // Introduce a delay or wait for a response from the client
    bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    if (bytesRead <= 0) {
        fprintf(stderr, "Error receiving username: %d\n", WSAGetLastError());
        closesocket(clientSocket);
        return;
    }

    buffer[bytesRead] = '\0';

    // Now 'buffer' contains the user's response (username)
    char username[20];
    strcpy(username, buffer);
    printf("Received username: %s\n", username);

    // Send a prompt for the password
    const char* passwordPrompt = "password: ";
    send(clientSocket, passwordPrompt, strlen(passwordPrompt), 0);

    // Receive the password from the client
    bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    if (bytesRead <= 0) {
        fprintf(stderr, "Error receiving password: %d\n", WSAGetLastError());
        closesocket(clientSocket);
        return;
    }

    buffer[bytesRead] = '\0'; // Null-terminate the received data

    // Now 'buffer' contains the password entered by the client
    char password[20];
    strcpy(password, buffer);
    printf("Received password: %s\n", password);

    // Check if the username and password are valid
    printf("Before calling isValidUser. username: %s, password: %s\n", username, password);

    if (isValidUser(username, password, users, MAX_USERS)) {
        printf("Valid username and password\n");

        const char* banner =
            "███╗   ██╗███████╗██╗  ██╗██╗   ██╗███████╗\r\n"
            "████╗  ██║██╔════╝╚██╗██╔╝██║   ██║██╔════╝\r\n"
            "██╔██╗ ██║█████╗   ╚███╔╝ ██║   ██║███████╗\r\n"
            "██║╚██╗██║██╔══╝   ██╔██╗ ██║   ██║╚════██║\r\n"
            "██║ ╚████║███████╗██╔╝ ██╗╚██████╔╝███████║\r\n"
            "╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝\r\n"
            "      --**Welcome To Nexus Network**--- ";

        send(clientSocket, banner, strlen(banner), 0);

        while (1) {
            // Receive data from the client
            bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);

            if (bytesRead <= 0) {
                // If the client disconnects or an error occurs, break from the loop
                closesocket(clientSocket);
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
        // Invalid credentials, send an error message to the client
        const char* errorMsg = "Invalid username or password. Please try again.\r\n";
        send(clientSocket, errorMsg, strlen(errorMsg), 0);
    }
}
