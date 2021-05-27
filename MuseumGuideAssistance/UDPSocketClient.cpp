#include "UDPSocketClient.h"
#include <string>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#pragma comment (lib, "ws2_32.lib")
UDPSocket::UDPSocket(const char* IP, int PortIn, int PortOut) :
    out{}, in{}, server{}, serverHint{}, client{}, clientLength{}, buf{}
{
    WSADATA data;
    WORD version = MAKEWORD(2, 2);

    // Start WinSock
    int wsOk = WSAStartup(version, &data);
    if (wsOk != 0) {
        // Not ok! Get out quickly
        std::cout << "Can't start Win sock! " << wsOk;
        return;
    }

    ////////////////////////////////////////////////////////////
    // CONNECT TO THE SERVER
    ////////////////////////////////////////////////////////////

    // Create a hint structure for the server
    this->server.sin_family = AF_INET; // AF_INET = IPv4 addresses
    this->server.sin_port = htons(PortIn); // Little to big endian conversion
    inet_pton(AF_INET, IP, &this->server.sin_addr); // Convert from string to byte array
    this->out = socket(AF_INET, SOCK_DGRAM, 0);

    // Create a socket, notice that it is a user datagram socket (UDP)
    this->in = socket(AF_INET, SOCK_DGRAM, 0);

    // Create a server hint structure for the server
    this->serverHint.sin_addr.S_un.S_addr = ADDR_ANY; // Use any IP address available on the machine
    this->serverHint.sin_family = AF_INET; // Address format is IPv4
    this->serverHint.sin_port = htons(PortOut); // Convert from little to big endian

    // Try and bind the socket to the IP and port
    if (bind(in, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR) {
        std::cout << "Can't bind socket! " << WSAGetLastError() << std::endl;
        return;
    }
    this->clientLength = sizeof(client); // The size of the client information
}
UDPSocket::~UDPSocket() {
    closesocket(this->out);
    closesocket(this->in);
    // Close down Win sock
    WSACleanup();
}
void UDPSocket::SendUDPData(std::string s) {
    int sendOk = sendto(this->out, s.c_str(), s.size() + 1, 0, ((sockaddr*)&this->server), sizeof(this->server));

    if (sendOk == SOCKET_ERROR) {
        std::cout << "That didn't work! " << WSAGetLastError() << std::endl;
    }
}

char* UDPSocket::ReciveData() {
    unsigned long iMode = 1;
    int nRet;

    ZeroMemory(&client, clientLength); // Clear the client structure
    ZeroMemory(buf, 1024); // Clear the receive buffer

    //Set socket to non blocking mode
    nRet = ioctlsocket(in, FIONBIO, (unsigned long*)&iMode);

    if (nRet == SOCKET_ERROR) {
        std::cout << "Failed to put in non blocking mode";
    }
    int bytesIn = recv(in, buf, 1024, 0);

    // Display message and client info
    char clientIp[256]; // Create enough space to convert the address byte array
    ZeroMemory(clientIp, 256); // to string of characters

    // Convert from byte array to chars
    inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);
    return buf;
}