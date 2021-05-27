#pragma once
#include <string>  
#include <WS2tcpip.h>
#include <iostream>

/// @brief Klasa tworząca komunikacje klient serwer UDP
/// @author Dominik Tekiela
/// @date 27.05.2021
class UDPSocket {
    /// @brief Zmienne do utworzenia połączenia klient - serwer 
    SOCKET out;
    /// @brief Zmienne do utworzenia połączenia klient - serwer 
    SOCKET in;
    /// @brief Zmienne do utworzenia połączenia klient - serwer 
    sockaddr_in server;
    /// @brief Zmienne do utworzenia połączenia klient - serwer 
    sockaddr_in serverHint;
    /// @brief Zmienne do utworzenia połączenia klient - serwer 
    sockaddr_in client;
    /// @brief Zmienne do utworzenia połączenia klient - serwer 
    int clientLength;
    /// @brief Zmienne do utworzenia połączenia klient - serwer 
    char buf[1024];
public:
    /// @brief Konstruktor łączący sie z danym IP na porcie OUT.
    /// @param IP IP komputera, z którym nasza aplikacja ma sie łączyć
    /// @param PortIn Port na otrzymywanie danych od połączonego klienta
    /// @param PortOut Port, na który wysyłane są binarnie dane
    UDPSocket(const char* IP, int PortIn, int PortOut);

    /// Destruktor - niszczy połączenie z klientem
    ~UDPSocket();

    /// @brief Wysyła string do klienta podanego w konstruktorze
    /// @param s Zmienna typu string, konwertowana jest na bity i wysyłana przez UDP do klienta
    void SendUDPData(std::string s);

    /// @brief Otwiera nasz serwer na otrzymywanie danych od klienta
    /// @return Zwraca tablice char* z otrzymanymi danymi
    char* ReciveData();
};

