#include "help_command.h"
#include <string.h>  // Include the header for 'strlen'
#include <sys/socket.h>

const char* tf= "aaqweqwewerwetqretqg";

void executeHelpCommand(int clientSocket, const char* tf) {
    send(clientSocket, tf, strlen(tf), 0);
}

// Register the command during initialization
__attribute__((constructor))
void registerHelpCommand() {
    registerCommand("help", executeHelpCommand);
}
