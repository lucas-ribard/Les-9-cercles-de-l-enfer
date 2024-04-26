#ifndef __LPTF_SOCKET_H__
#define __LPTF_SOCKET_H__

#include <string>
#include <memory>
#include <netinet/in.h>

class LPTF_Socket {
private:
    int sockfd;
    sockaddr_in address;
    struct sockaddr_in clientAddress; // Client's address
    void setupAddress(int port);

public:
    LPTF_Socket(); // Default constructor
    ~LPTF_Socket(); // Destructor
    LPTF_Socket(const LPTF_Socket&); // Copy constructor
    LPTF_Socket &operator=(const LPTF_Socket&); // Affectation operator

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
