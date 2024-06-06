#include "../include/Server.hpp"

std::string Server::generateUUID() {
    static boost::uuids::random_generator generator;
    boost::uuids::uuid id = generator();
    return to_string(id);
}

// std::string clientExecutor(std::unique_ptr<LPTF_Socket> client, std::string clientID) {

// }

// void selectClient(std::unique_ptr<LPTF_Socket> client, std::string clientID) {
    
// }

Server::Server(int port)
{
    // listener = listenSocket();
    // listener_socket = std::make_unique<LPTF_Socket>();

    // Bind and listen
    this->serverSocket.bindSocket(port);
    this->serverSocket.listenSocket();
    this->serverSocket.setNonBlocking(true);  // Set the socket to non-blocking mode
    std::cout << "Server Ready. Non-blocking mode is activated." << std::endl;
    memset(&this->clientsPollFD, 0, sizeof(this->clientsPollFD));
}

Server::~Server()
{
    std::cout << "Server destroyer called" << std::endl;
    
}

std::vector<struct pollfd> Server::getClientsPollFD()
{
    return this->clientsPollFD;
}


void Server::setServerSocket(LPTF_Socket serverSocket)
{
    this->serverSocket = serverSocket;
}

LPTF_Socket Server::getServerSocket()
{
    return this->serverSocket;
}

void Server::handleClient(std::unique_ptr<LPTF_Socket> client, std::string clientID) {
    try {
        std::string displayID = clientID.length() >= 5 ? clientID.substr(0, 5) : clientID; // make a display ID for the client
        std::string clientIP = client->getClientIP();

        std::cout << "User #" << displayID << " connected from : "<< clientIP << std::endl;

        // this.clientsPollFD.push_back(client);

        while (true) {  // Keep the session alive until disconnected

            std::string msg = client->receiveMsg();
            
            if (msg.empty()) {
                std::cout << "User #" << displayID << " disconnected." << std::endl;
                break;  // Exit loop if an empty message is received, indicating disconnection
            }
            
            std::cout << "Message received from User #" << displayID << " : " << msg << std::endl;
               
            client->sendMsg("Server received: " + msg);
        }
    } catch (const std::exception& e) {
        std::cerr << "Client Handling Exception: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "Server starting..." << std::endl;

    try {
        Server server = Server(8888);
        // struct pollfd clientsPoll;
        std::vector<struct pollfd> clientsPoll;
        int ready;
            // If valid socket descriptor then add to read list
            if (sd > 0) {
                FD_SET(sd, &readfds);
            }

            // Highest file descriptor number, needed for the select function
            if (sd > max_sd) {
                max_sd = sd;
            }
        }


        // LPTF_Socket serverSocket;
        // serverSocket.bindSocket(8888);
        // serverSocket.listenSocket();
        // serverSocket.setNonBlocking(true);  // Set the socket to non-blocking mode
        // std::cout << "Server Ready. Non-blocking mode is activated." << std::endl;

        // memset(&clientsPoll, 0, sizeof(clientsPoll));

        while (true) {
            clientsPoll = server.getClientsPollFD();
            // ready = poll(&clientsPoll, 100, -1);

            // clientsPoll.fd = 0;

            if (ready == -1) {
                exit(-1);
            }



            // std::string input;
            // std::cout << "Enter input: ";
            // std::getline(std::cin, input);
            // std::cout << "input: " << input << std::endl;

            // if (input == "q") exit(0);
            auto client = server.getServerSocket().acceptSocket();
            if (client == nullptr) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait a bit before trying again to avoid busy waiting
                continue;  // No client to process, continue checking
            }
            // std::cout << "Client connected." << std::endl;
            // server.getClientsPollFD.push_back(client);

            std::cout << "new client connected at " << client->getClientIP();
            // std::string clientID = Server::generateUUID();  // Generate a unique UUID for each client

            // handleClient(client, clientId);


            

            // std::thread clientThread(Server::handleClient, std::move(client), clientID);
            // clientThread.detach(); // Detach the thread to allow it to run independently
        }
    } catch (const std::exception& e) {
        std::cerr << "Server Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}