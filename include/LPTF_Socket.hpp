#ifndef __LPTF_SOCKET_H__
#define __LPTF_SOCKET_H__

#include <string>
#include <memory>
#include <netinet/in.h>
#include <stdexcept>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

class LPTF_Socket {
private:
    int sockfd;
    sockaddr_in address;
    struct sockaddr_in clientAddress; // Client's address
    void setupAddress(int port);

public:
    LPTF_Socket(); // Default constructor
    // ~LPTF_Socket(); // Destructor
    // LPTF_Socket(const LPTF_Socket& socket); // Copy constructor
    // LPTF_Socket &operator=(const LPTF_Socket& socket); // Affectation operator

    ~LPTF_Socket()
    {
        close(sockfd);
    }

    // Copy constructor
    LPTF_Socket(const LPTF_Socket& socket)
    {
        std::cout << "Copy constructor of LPTF_Socket called" << std::endl;
        sockfd = socket.sockfd;
    }

    // Affectation operator
    LPTF_Socket &operator=(const LPTF_Socket& socket)
    {
        std::cout << "Affectation operator constructor of LPTF_Socket called" << std::endl;
        return *this;
    }


    int getSockfd();
    void setSockfd(int sockfd);

    void bindSocket(int port);
    void listenSocket();
    std::unique_ptr<LPTF_Socket> acceptSocket();
    void connectSocket(const std::string& ip, int port);
    ssize_t sendMsg(const std::string& message);
    std::string receiveMsg();
    std::string getClientIP();
    void setNonBlocking(bool enable);
};

#endif // LPTF_SOCKET_H
