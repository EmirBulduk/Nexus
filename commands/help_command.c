// help_command.c
#include "headers/help_command.h"
#include "../src/headers/cman.h"
#include <string.h>

void executeHelpCommand(int clientSocket, const char* args) {
    const char* helpMsg = "Available commands:\r\n"
                          "help - Display this help message\r\n"
                          "echo [message] - Display the provided message\r\n"
                          "quit - Disconnect from the server\r\n";
    send(clientSocket, helpMsg, strlen(helpMsg), 0);
}

// Register the command during initialization
__attribute__((constructor))
void registerHelpCommand() {
    registerCommand("help", executeHelpCommand);
}
