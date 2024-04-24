#include <iostream>
#include "LPTF_Socket.h"

int main() {
    printf("Server starting");
    try {
        LPTF_Socket serverSocket;
        serverSocket.bindSocket(8888);
        serverSocket.listenSocket();

        while (true) {
            auto client = serverSocket.acceptSocket();
            std::string msg = client->receiveMsg();
            std::cout << "Message received: " << msg << std::endl;
            client->sendMsg("Hello from server");
        }
    } catch (const std::exception& e) {
        std::cerr << "Server Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
