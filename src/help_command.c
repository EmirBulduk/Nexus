// help_command.c
#include "help_command.h"
#include <string.h>
#include <sys/socket.h>

const char* helpMsg = "This is the help message. Type 'echo' for an example.\r\n";

void executeHelpCommand(int clientSocket, const char* args) {
    send(clientSocket, helpMsg, strlen(helpMsg), 0);
}

// Register the command during initialization
__attribute__((constructor))
void registerHelpCommand() {
    registerCommand("help", executeHelpCommand);
}
