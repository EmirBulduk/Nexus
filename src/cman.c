// commands.c
#include "headers/cman.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>  // Include the header for 'send'

#define MAX_COMMANDS 10

// Array to store registered commands
static Command commands[MAX_COMMANDS];
static int numCommands = 0;

// Function to initialize the command handler
void initializeCommandHandler() {
    // Initialize the array of commands
    numCommands = 0;
}

// Function to register a command
bool registerCommand(const char* name, CommandHandler handler) {
    if (numCommands < MAX_COMMANDS) {
        // Register the command in the array
        commands[numCommands].name = name;
        commands[numCommands].handler = handler;
        numCommands++;
        return true;
    } else {
        fprintf(stderr, "Maximum number of commands reached\n");
        return false;
    }
}

// Function to execute a command
void executeCommand(int clientSocket, const char* command) {
    // Split the command into name and arguments
    char commandName[50];
    char commandArgs[50];

    int argsCount = sscanf(command, "%s %[^\n]", commandName, commandArgs);

    // Find and execute the registered command
    for (int i = 0; i < numCommands; i++) {
        if (strcmp(commands[i].name, commandName) == 0) {
            commands[i].handler(clientSocket, commandArgs);
            return;
        }
    }

    // If the command is not found, send an error message
    const char* errorMsg = "Invalid command. Type 'help' for a list of commands.\r\n";
    send(clientSocket, errorMsg, strlen(errorMsg), 0);
}