#include <iostream>
#include <thread>
#include <mutex>
#include <map>
#include <string>
#include <random>
#include "../include/LPTF_Socket.hpp"

// Global map to store client connections
std::map<std::string, std::unique_ptr<LPTF_Socket>> clients;
std::mutex clientsMutex;

// Function to generate a 5-character alphanumeric ID
std::string generateShortID() {
    const std::string chars =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, chars.size() - 1);

    std::string id;
    for (int i = 0; i < 5; ++i) {
        id += chars[distribution(generator)];
    }
    return id;
}
// function to handle client connections
void handleClient(std::unique_ptr<LPTF_Socket> client, std::string clientID) {
    try {
        std::string clientIP = client->getClientIP();
        std::cout << "User #" << clientID << " connected from: " << clientIP << std::endl;
        client->sendMsg("Connection accepted");

        {
            std::lock_guard<std::mutex> lock(clientsMutex);
            clients[clientID] = std::move(client);
        }

        while (true) {
            std::string clientMsg = clients[clientID]->receiveMsg();
            
            if (clientMsg.empty()){
                std::cout << "User #" << clientID << " disconnected." << std::endl;
                break;  // Exit loop if an empty message is received, indicating disconnection
            }
            
            std::cout << "Message received from User #" << clientID << ": " << clientMsg << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Client Handling Exception: " << e.what() << std::endl;
    }

    {
        std::lock_guard<std::mutex> lock(clientsMutex);
        clients.erase(clientID);
    }
}
// Function to handle console input for sending messages to clients
void consoleInputHandler() {
    while (true) {
        std::string input;
        std::getline(std::cin, input);

        std::size_t spacePos = input.find(' ');
        if (spacePos != std::string::npos) {
            std::string clientID = input.substr(0, spacePos);
            std::string message = input.substr(spacePos + 1);

            std::lock_guard<std::mutex> lock(clientsMutex);
            if (clients.find(clientID) != clients.end()) {
                clients[clientID]->sendMsg(message);
            } else {
                std::cout << "No client found with ID: " << clientID << std::endl;
            }
        } else {
            std::cout << "Invalid input. Format: <clientID> <message>" << std::endl;
        }
    }
}

int main() {
    std::cout << "Server starting..." << std::endl;

    std::thread(consoleInputHandler).detach();

    try {
        LPTF_Socket serverSocket;
        serverSocket.bindSocket(8888);
        serverSocket.listenSocket();
        serverSocket.setNonBlocking(true);  // Set the socket to non-blocking mode
        std::cout << "Server Ready" << std::endl;

        while (true) {
            auto client = serverSocket.acceptSocket();
            if (client == nullptr) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait a bit before trying again to avoid busy waiting
                continue;  // No client to process, continue checking
            }
            std::cout << "Client connected." << std::endl;
            std::string clientID = generateShortID();  // Generate a short 5-character ID for each client
            
            std::thread clientThread(handleClient, std::move(client), clientID);
            clientThread.detach(); // Detach the thread to allow it to run independently
        }
    } catch (const std::exception& e) {
        std::cerr << "Server Exception: " << e.what() << std::endl;
        
        return 1;
    }
    return 0;
}
