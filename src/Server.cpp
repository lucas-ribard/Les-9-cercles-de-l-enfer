#include <iostream>
#include <thread>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "../include/LPTF_Socket.hpp"

// Function to generate a UUID
std::string generateUUID() {
    static boost::uuids::random_generator generator;
    boost::uuids::uuid id = generator();
    return to_string(id);
}

void handleClient(std::unique_ptr<LPTF_Socket> client, std::string clientID) {
    try {
        std::string displayID = clientID.length() >= 5 ? clientID.substr(0, 5) : clientID; // make a display ID for the client
        std::string clientIP = client->getClientIP();
        std::cout << "User #" << displayID << " connected from : "<< clientIP << std::endl;
        client->sendMsg("Connection accepted") << std::endl;  //Demande

        while (true) {  // Keep the session alive until disconnected

            // déroulé temporaire :
                // le serveur envoie un premier message ( string pour l'instant mais ca chagera pour des ordres )
                // le cloient répond
                // le serveur confirme 


            client->sendMsg("waiting for your input") << std::endl;  //Demande

            std::string msg = client->receiveMsg();  //Attend La réponse
            
            if (msg.empty()){
                std::cout << "User #" << displayID << " disconnected." << std::endl;
                break;  // Exit loop if an empty message is received, indicating disconnection
            }
            
            std::cout << "Message received from User #" << displayID << " : " << msg << std::endl;
               
            client->sendMsg("i received: " + msg);     //confirme
        }
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
        serverSocket.setNonBlocking(true);  // Set the socket to non-blocking mode
        std::cout << "Server Ready. Non-blocking mode is activated." << std::endl;

        while (true) {
            //std::cout << "Waiting for a client to connect..." << std::endl;

            auto client = serverSocket.acceptSocket();
            if (client == nullptr) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait a bit before trying again to avoid busy waiting
                continue;  // No client to process, continue checking
            }
            std::cout << "Client connected." << std::endl;
            std::string clientID = generateUUID();  // Generate a unique UUID for each client
            
            std::thread clientThread(handleClient, std::move(client), clientID);
            clientThread.detach(); // Detach the thread to allow it to run independently
        }
    } catch (const std::exception& e) {
        std::cerr << "Server Exception: " << e.what() << std::endl;
        std::cerr << "Error code: " << errno << " (" << std::strerror(errno) << ")" << std::endl;
    return 1;
}
    return 0;
}