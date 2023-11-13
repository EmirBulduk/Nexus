
#ifndef CMAN_H
#define CMAN_H

#include <stdbool.h>

// Function signature for a command handler
typedef void (*CommandHandler)(int clientSocket, const char* args);

// Structure to represent a command
typedef struct {
    const char* name;
    CommandHandler handler;
} Command;

// Function to initialize the command handler
void initializeCommandHandler();

// Function to register a command
bool registerCommand(const char* name, CommandHandler handler);

// Function to execute a command
void executeCommand(int clientSocket, const char* command);


//helps us counting commands
void getCommandCount(int* countPtr);


#endif
