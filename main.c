#include <stdio.h>
#include <winsock2.h>

#define PORT 23
#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

void handleClient(SOCKET clientSocket);

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "Failed to initialize Winsock\n");
        return 1;
    }

    SOCKET serverSocket
    = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        fprintf(stderr, "Failed to create socket\n");
        WSACleanup();
        return 1;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        fprintf(stderr, "Bind failed with error: %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    if (listen(serverSocket, MAX_CLIENTS) == SOCKET_ERROR) {
        fprintf(stderr, "Listen failed with error: %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("Telnet server is listening on port %d...\n", PORT);

    while (1) {
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            fprintf(stderr, "Accept failed with error: %d\n", WSAGetLastError());
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        printf("Client connected\n");

        // Handle the client in a separate function
        handleClient(clientSocket);

        // Close the client socket after handling the connection
        closesocket(clientSocket);

        printf("Client disconnected\n");
    }

    // Cleanup Winsock
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}

void handleClient(SOCKET clientSocket) {
    char buffer[BUFFER_SIZE];
    int bytesRead;

    // Send a welcome message to the client
    const char* welcomeMsg = "Welcome to the simple Telnet server!\r\n";
    const char* banner = "Banner there it goes ";
    send(clientSocket, welcomeMsg, strlen(welcomeMsg), 0);
    send(clientSocket, banner, strlen(banner), 0);

    while (1) {
        // Receive data from the client
        bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);

        if (bytesRead <= 0) {
            // If the client disconnects or an error occurs, break from the loop
            break;
        }

        // Process the received data (you can implement your Telnet server logic here)
        // For simplicity, we'll just echo the received data back to the client
        send(clientSocket, buffer, bytesRead, 0);
    }
}
