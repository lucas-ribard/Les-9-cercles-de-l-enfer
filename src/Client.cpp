#include <iostream>

// change the logic to check the os so that it will 
// change the lpft path, so we keep the function names but 
// change the system calls behind
#include "../include/LPTF_Socket.hpp"

int main() {

      #ifdef _WIN32
    std::cout << "Running on Windows OS\n";
    
    #elif __linux__ //if on linux, run linux client
   
    try {
        LPTF_Socket clientSocket;
        clientSocket.connectSocket("127.0.0.1", 8888);
        std::cout << "(type 'exit' to quit)" << std::endl;
        while (true) {
            std::cout << clientSocket.receiveMsg() << std::endl; // Attend la requete
            std::string msg;
            std::cout << "Enter message : ";
            std::getline(std::cin, msg);  // il repond

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


    #elif __APPLE__
    std::cout << "Running on Apple OS\n";

    #else
    std::cout << "Unsupported OS\n";

    #endif

    return 0;
}
