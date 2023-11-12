//
// Created by Arch64 on 11.11.2023.
//

#include "../headers/echo_command.h"
#include <string.h>



#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") // Link with ws2_32.lib
#else
#include <sys/socket.h>
#endif

void executeEchoCommand(int clientSocket, const char* args) {
    const char*  mf = "hello mf ";

    send(clientSocket, mf, strlen(mf), 0);

}

// Register the command during initialization
__attribute__((constructor))
void registerEchoCommand() {
    registerCommand("echo", executeEchoCommand);
}