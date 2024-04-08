//
// Created by buldu on 8.04.2024.
//

#include "whois.h"
#include "../cman.h"
#include <sys/socket.h>


void checkip(int clientSocket, const char* ip) {
    char response[1024];
    char* ip = strtok(ip, " ");
    if (ip == NULL) {
        strcpy(response, "Usage: whois <ip>\n");
        send(clientSocket, response, strlen(response), 0);
        return;
    }
    strcpy(response, "Checking IP: ");
    strcat(response, ip);
    strcat(response, "\n");


    send(clientSocket, response, strlen(response), 0);
}

void executeWhoiscommand(int clientSocket, const char* args) {
    char response[1024];

    char* ip = strtok(args, " ");

    checkip(clientSocket, ip);

    send(clientSocket, response, strlen(response), 0);
}



//register
void registerWhoiscommand() {
    registerCommand("whois", executeWhoiscommand);
}


