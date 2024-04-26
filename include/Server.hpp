#ifndef __SERVER__
#define __SERVER__

#include <string>
#include <iostream>
#include <thread>
#include <boost/uuid/uuid.hpp>
#include <poll.h>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "../include/LPTF_Socket.hpp"

class Server
{
    public:
        Server();
        Server(const Server&);
        ~Server();
        Server &operator=(const Server&); // Affectation operator
        pollfd *getPfds();
        void setPfds(pollfd *pfds);
        static void handleClient(std::unique_ptr<LPTF_Socket> client, std::string clientID);
        static std::string generateUUID();

    private:
        struct pollfd *pfds;


};

#endif