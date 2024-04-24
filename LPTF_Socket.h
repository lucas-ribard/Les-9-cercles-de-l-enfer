#ifndef LPTF_SOCKET_H
#define LPTF_SOCKET_H

#include <string>
#include <memory>
#include <netinet/in.h>

class LPTF_Socket {
private:
    int sockfd;
    sockaddr_in address;

    void setupAddress(int port);

public:
    LPTF_Socket();
    ~LPTF_Socket();

    void bindSocket(int port);
    void listenSocket();
    std::unique_ptr<LPTF_Socket> acceptSocket();
    void connectSocket(const std::string& ip, int port);
    ssize_t sendMsg(const std::string& message);
    std::string receiveMsg();
};

#endif // LPTF_SOCKET_H
