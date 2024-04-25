#include <iostream>
#include "../include/LPTF_Socket.hpp"

int main() {
    try {
        LPTF_Socket clientSocket;
        clientSocket.connectSocket("10.10.30.146", 8888);
        std::cout << "(type 'exit' to quit)" << std::endl;
        while (true) {
            std::string msg;
            std::cout << "Enter message : ";
            std::getline(std::cin, msg);

            if (msg == "exit") {// Exit the loop if the user types 'exit'
                break; 
            }

            clientSocket.sendMsg(msg); // Send the user input to the server
            std::cout << clientSocket.receiveMsg() << std::endl; // Receive and print the response from the server
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Client Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
