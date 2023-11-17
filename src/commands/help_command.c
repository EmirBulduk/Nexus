// help_command.c
#include "help_command.h"
#include "cman.h"

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#define STATS "EAP"

void executeHelpCommand(int clientSocket, const char* args) {

    int commandCount;
    getCommandCount(&commandCount);

    int bots = 200;

    char helpMsg[200];

    snprintf(helpMsg, sizeof(helpMsg), "----------------\r\n"
                                       "      Nexus     \r\n"
                                       "connected bots: %d\r\n"
                                       "registered commands: %d\r\n"
                                       "Status: %S"
                                       "----------------\r\n", bots, commandCount, STATS);

    send(clientSocket, helpMsg, strlen(helpMsg), 0);
}

__attribute__((constructor))
void registerHelpCommand() {
    registerCommand("help", executeHelpCommand);
}
