// commands.c
#include "cman.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>

#define MAX_COMMANDS 50

// Array to store registered commands
static Command commands[MAX_COMMANDS];
static int numCommands = 0;
static int commandCount = 0;
static char lastcommand[50];

// Function to initialize the command handler
void initializeCommandHandler() {
    // Initialize the array of commands
    numCommands = 0;
    commandCount = 0;
    lastcommand[0] = '\0';
}

// Function to register a command
bool registerCommand(const char* name, CommandHandler handler) {
    if (numCommands < MAX_COMMANDS) {
        // Allocate memory for the command name and copy the string
        commands[numCommands].name = strdup(name);

        if (commands[numCommands].name == NULL) {
            // Handle memory allocation failure
            fprintf(stderr, "Memory allocation error\n");
            return false;
        }

        commands[numCommands].handler = handler;
        numCommands++;
        commandCount++;
        return true;
    } else {
        fprintf(stderr, "Maximum number of commands reached\n");
        return false;
    }
}

void getCommandCount(int* countPtr) {
    *countPtr = commandCount;
}

void executeCommand(int clientSocket, const char* command) {
    // Split the command into name and arguments
    char commandName[50];
    char commandArgs[50];
    int argsCount = sscanf(command, "%s %[^\n]", commandName, commandArgs);
    // Check if the current command is the same as the last command
    if (strcmp(command, lastcommand) == 0) {
        return;  // Avoid sending the error message for the same command
    }
    // Update the lastCommand variable
    strncpy(lastcommand, command, sizeof(lastcommand));
    lastcommand[sizeof(lastcommand) - 1] = '\0';  // Ensure null-termination
    // Find and execute the registered command
    for (int i = 0; i < numCommands; i++) {
        if (strcmp(commands[i].name, commandName) == 0) {
            commands[i].handler(clientSocket, commandArgs);
            return;
        }
    }
    // If the command is not found, send an error message
    const char* errorMsg = "Invalid command enter 'help' For Help\r\n";
    send(clientSocket, errorMsg, strlen(errorMsg), 0);
}