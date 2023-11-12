//
// Created by Arch64 on 11.11.2023.
//

#include "echo_command.h"
#include <string.h>



void executeEchoCommand(int clientSocket, const char* args) {

    const char* Echo = "No_echo";

    send(clientSocket, helpMsg, strlen(Echo), 0);
}

// Register the command during initialization
__attribute__((constructor))
void registerEchoCommand() {
    registerCommand("echo", executeEchoCommand);
}
