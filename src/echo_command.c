// echo_command.c
#include "echo_command.h"
#include <string.h>  // Include the header for 'strlen'
#include <sys/socket.h>

const char* mf= "Echo. \r\n";

void executeEchoCommand(int clientSocket, const char* mf) {
    send(clientSocket, mf, strlen(mf), 0);
}

// Register the command during initialization
__attribute__((constructor))
void registerEchoCommand() {
    registerCommand("echo", executeEchoCommand);
}
