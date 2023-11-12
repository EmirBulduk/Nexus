// echo_command.c
// ... (other includes)
#include "../headers/echo_command.h"
#include <sys/socket.h>

// ... (other functions)

void executeEchoCommand(int clientSocket, const char* args) {
    const char*  mf = "hello mf ";

    // Ensure proper inclusion of headers for the send function
    send(clientSocket, mf, strlen(mf), 0);
}

// ... (other functions)

// Register the command during initialization
__attribute__((constructor))
void registerEchoCommand() {
    registerCommand("echo", executeEchoCommand);
}
