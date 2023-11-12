// help_command.c
#include "../headers/help_command.h"
#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") // Link with ws2_32.lib
#else
#include <sys/socket.h>
#endif

void executeHelpCommand(int clientSocket, const char* args) {
    const char* helpMsg = "Available commands:\r\n"
                          "help - Display this help message\r\n"
                          "echo [message] - Display the provided message\r\n"
                          "quit - Disconnect from the server\r\n";

    // Ensure proper inclusion of headers for the send function
    send(clientSocket, helpMsg, strlen(helpMsg), 0);
}

// Register the command during initialization
__attribute__((constructor))
void registerHelpCommand() {
    registerCommand("help", executeHelpCommand);
}