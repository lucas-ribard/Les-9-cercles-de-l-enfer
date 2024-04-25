#include "LPTF_Socket.h"
#include <stdexcept>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

LPTF_Socket::LPTF_Socket() : sockfd(socket(AF_INET, SOCK_STREAM, 0)) {
    if (sockfd < 0) {
        throw std::runtime_error("Socket creation failed");
    }
}

LPTF_Socket::~LPTF_Socket() {
    close(sockfd);
}

void LPTF_Socket::setupAddress(int port) {
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;
}

void LPTF_Socket::bindSocket(int port) {
    setupAddress(port);
    if (bind(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        throw std::runtime_error("Bind failed");
    }
}

void LPTF_Socket::listenSocket() {
    if (listen(sockfd, 5) < 0) {
        throw std::runtime_error("Listen failed");
    }
}

std::unique_ptr<LPTF_Socket> LPTF_Socket::acceptSocket() {
    int addrlen = sizeof(address);
    int new_socket = accept(sockfd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    if (new_socket < 0) {
        throw std::runtime_error("Accept failed");
    }
    std::unique_ptr<LPTF_Socket> newConn(new LPTF_Socket);
    newConn->sockfd = new_socket;
    return newConn;
}

void LPTF_Socket::connectSocket(const std::string& ip, int port) {
    setupAddress(port);
    address.sin_addr.s_addr = inet_addr(ip.c_str());
    if (connect(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        throw std::runtime_error("Connection failed");
    }
}

ssize_t LPTF_Socket::sendMsg(const std::string& message) {
    return send(sockfd, message.c_str(), message.size(), 0);
}

std::string LPTF_Socket::receiveMsg() {
    char buffer[1024] = {0};
    ssize_t valread = recv(sockfd, buffer, 1024, 0);
    if (valread < 0) {
        throw std::runtime_error("Read failed");
    }
    return std::string(buffer, valread);
}

std::string LPTF_Socket::getClientIP() {
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(this->clientAddress.sin_addr), client_ip, INET_ADDRSTRLEN);
    return std::string(client_ip);
}