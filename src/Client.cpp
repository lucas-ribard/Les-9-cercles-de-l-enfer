#include <iostream>
#include <string> 
#include "../include/LPTF_Packet.hpp"

// load a different header file based on the OS
 #ifdef _WIN32
    std::cout << "Running on Windows OS\n";
    //need driss to do the windows library
    
    #elif __linux__ //if on linux, run linux client
        #include "../include/LPTF_Socket.hpp"
        

    #elif __APPLE__
    std::cout << "Running on Apple OS\n";
    //bruh

    #else
    std::cout << "Unsupported OS\n";

    #endif

void systemCall(const char* command){
  #if defined _WIN32
    system("cls");
        //clrscr(); // including header file : conio.h
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
        //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
    #elif defined (__APPLE__)
        system("clear");
    #endif
}



int main() {
    systemCall("ls");

    std::string msg;

    try {
        LPTF_Socket clientSocket;
        clientSocket.connectSocket("127.0.0.1", 8888);
        std::cout << "(type 'exit' to quit)" << std::endl;
        while (true) {
            std::cout << "Server : " << clientSocket.receiveMsg() << std::endl; // Attend la requete
            
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

}
