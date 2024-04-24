#include <iostream>
#include "LPTF_Socket.h"

#include <iostream>

int main() {
    try {
        LPTF_Socket clientSocket;
        clientSocket.connectSocket("127.0.0.1", 8888);
        std::string msg = "Hello from client"; 
        getline(std::cin, msg);
        
        clientSocket.sendMsg(msg); // send Message 
        std::cout << "Response from server: " << clientSocket.receiveMsg() << std::endl; // receive and write Message 
    } catch (const std::exception& e) {
        std::cerr << "Client Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
