#include <iostream>
#include <thread>
#include "LPTF_Socket.h"

void handleClient(std::unique_ptr<LPTF_Socket> client) {
    try {
        std::string msg = client->receiveMsg();
        std::cout << "Message received: " << msg << std::endl;
        client->sendMsg("Server received: " + msg);
    } catch (const std::exception& e) {
        std::cerr << "Client Handling Exception: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "Server starting..." << std::endl;

    try {
        LPTF_Socket serverSocket;
        serverSocket.bindSocket(8888);
        serverSocket.listenSocket();

        while (true) {
            auto client = serverSocket.acceptSocket();
            std::thread clientThread(handleClient, std::move(client));
            clientThread.detach(); // Detach the thread to allow it to run independently
        }
    } catch (const std::exception& e) {
        std::cerr << "Server Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
