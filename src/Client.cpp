#include <iostream>
#include <string>
#include "../include/LPTF_Packet.hpp"

// Load a different header file based on the OS
#ifdef _WIN32
    std::cout << "Running on Windows OS\n";
    // Need to implement the Windows client code

#elif __linux__ // If on Linux, run Linux client
    #include "../include/LPTF_Socket.hpp"

#elif __APPLE__
    std::cout << "Running on Apple OS\n";
    // Need to implement the macOS client code

#else
    std::cout << "Unsupported OS\n";
#endif

void systemCall(const char* command) {
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}

int main() {
    systemCall("ls");

    try {
        LPTF_Socket clientSocket;
        clientSocket.connectSocket("127.0.0.1", 8888);
        std::cout << "(type 'exit' to quit)" << std::endl;
        std::cout << "Server: " << clientSocket.receiveMsg() << std::endl;

        while (true) {
            std::string serverMsg = clientSocket.receiveMsg(); // Receive message from the server

            if (serverMsg.empty() || serverMsg == "exit") { // Exit the loop if the server message is empty or "exit"
                break;
            }

            std::cout << "Server: " << serverMsg << std::endl; // Print the server message

            clientSocket.sendMsg(serverMsg); // Respond with the same message received from the server
        }
    } catch (const std::exception& e) {
        std::cerr << "Client Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
