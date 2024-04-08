//
// Created by buldu on 8.04.2024.
//


#include "Attack_command.h"
#include "sys/socket.h"
#include "cman.h"

void executeAttackcommand(int clientSocket, const char* args) {

    if (args == NULL) {
        send(clientSocket, "Usage: attack <ip> <port> <time>\r\n", 35, 0);
        return;
    }
    send(clientSocket, "Attack command executed\r\n", 26, 0);
}
__attribute__((constructor))
void registerattackcommand() {
    registerCommand("attack", executeAttackcommand);
}
