//
// Created by buldu on 8.04.2024.
//


#include "syn_command.h"
#include "sys/socket.h"
#include "../cman.h"

void executeSyncommand(int clientSocket, const char* args) {

    char* ip = strtok(args, " ");
    char* port = strtok(nullptr, " ");
    char* time = strtok(nullptr, " ");

    if (args == nullptr) {
        send(clientSocket, "Usage: attack <ip> <port> <time>\r\n", 35, 0);
        return;
    }


    send(clientSocket, "Attack command executed\r\n", 26, 0);
}
__attribute__((constructor))
void registerattackcommand() {
    registerCommand("attack", executeSyncommand);
}
