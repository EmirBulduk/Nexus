#include "help_command.h"
#include "cman.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

void executeHelpCommand(int clientSocket, const char* args) {
    int commandCount;
    getCommandCount(&commandCount);
    int bots = 200;
    char helpMsg[500];
    const char* STATS = "EAP";
    snprintf(helpMsg, sizeof(helpMsg), "----------------\r\n"
                                       "      Nexus     \r\n"
                                       "connected bots: %d\r\n"
                                       "registered commands: %d\r\n"
                                       "Status: %s\r\n"
                                       "----------------\r\n", bots, commandCount, STATS);
    send(clientSocket, helpMsg, strlen(helpMsg), 0);
}
__attribute__((constructor))
void registerHelpCommand() {
    registerCommand("help", executeHelpCommand);
}
