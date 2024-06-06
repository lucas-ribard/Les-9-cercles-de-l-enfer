#ifndef __SERVER__
#define __SERVER__

#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <boost/uuid/uuid.hpp>
#include <poll.h>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "../include/LPTF_Socket.hpp"

class Server
{
    public:
        Server(int port);
        Server(const Server&);
        ~Server();
        Server &operator=(const Server&); // Affectation operator
        // struct pollfd getClientsPollFD();
        std::vector<struct pollfd> getClientsPollFD();
        void setClientsPollFD(pollfd clientsPollFD);

        void setServerSocket(LPTF_Socket serverSocket);
        LPTF_Socket getServerSocket();
        static void handleClient(std::unique_ptr<LPTF_Socket> client, std::string clientID);
        static std::string generateUUID();

    private:
        // struct pollfd clientsPollFD;
        std::vector<struct pollfd> clientsPollFD;
        LPTF_Socket serverSocket;


};

#endif