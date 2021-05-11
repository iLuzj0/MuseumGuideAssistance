#pragma once
#include <string>  
#include <WS2tcpip.h>
#include <iostream>

class UDPSocket {
    SOCKET out;
    SOCKET in;
    sockaddr_in server;
    sockaddr_in serverHint;
    sockaddr_in client;
    int clientLength;
    char buf[1024];
public:
    UDPSocket(const char* IP, int PortIn, int PortOut);
    ~UDPSocket();
    void SendUDPData(std::string s);
    char* ReciveData();
};

