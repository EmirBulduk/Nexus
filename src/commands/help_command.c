// help_command.c
#include "help_command.h"
#include "cman.h"  // Include the header file for registerCommand

#include <stdio.h>  // Include the header file for snprintf
#include <string.h>
#include <sys/socket.h>

void executeHelpCommand(int clientSocket, const char* args) {
    // Get the count of registered commands
    int commandCount;
    getCommandCount(&commandCount);

    // Initialize and declare the variable bots
    int bots = 200;

    // Create a buffer to store the message
    char helpMsg[200];  // Adjust the size as needed

    // Format the message with the count of registered commands and connected bots
    snprintf(helpMsg, sizeof(helpMsg), "----------------\r\n"
                                       "      Nexus     \r\n"
                                       "commands:\n\r"
                                       "----------------\r\n"
                                       "connected bots: %d\r\n"
                                       "registered commands: %d\r\n", bots, commandCount);

    // Send the message to the client
    send(clientSocket, helpMsg, strlen(helpMsg), 0);
}

// Register the command during initialization
__attribute__((constructor))
void registerHelpCommand() {
    registerCommand("help", executeHelpCommand);
}
