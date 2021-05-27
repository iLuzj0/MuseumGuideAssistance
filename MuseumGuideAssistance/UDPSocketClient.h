#pragma once
#include <string>  
#include <WS2tcpip.h>
#include <iostream>

/// @brief Klasa tworząca komunikacje klient serwer UDP
/// @author Dominik Tekiela
/// @date 27.05.2021
class UDPSocket {
    /// @brief Wyjściowy socket używany do połączenia klient - serwer
    SOCKET out;

    /// @brief Wejściowy socket używany do połączenia klient - serwer
    SOCKET in;

    /// @brief Zmienna serwera do obsługi winsock
    sockaddr_in server;

    /// @brief Podpowiedzi dla servera, głównie używane do informawania serwera o klientach
    sockaddr_in serverHint;

    /// @brief Zmienna klienta do obsługi winsock
    sockaddr_in client;

    /// @brief Wielkość danych otrzymywanych od klienta
    int clientLength;

    /// @brief Bufor dla przychodzących danych
    char buf[1024];
public:
    /// @brief Konstruktor startujący winsock
    /// Na podstawie uzyskanych IP tworzymy strukturę podpowiedzi dla serwera.
    /// Tworzymy socket UDP.
    /// Łączymy nasz socket z adresem IP oraz portem.
    /// @param IP IP komputera, z którym nasza aplikacja ma sie łączyć
    /// @param PortIn Port na otrzymywanie danych od połączonego klienta
    /// @param PortOut Port, na który wysyłane są binarnie dane
    UDPSocket(const char* IP, int PortIn, int PortOut);

    /// Destruktor - niszczy połączenie z klientem
    ~UDPSocket();

    /// @brief Wysyła string do klienta podanego w konstruktorze
    /// Użyta jest do tego metoda sendto.
    /// @param s Zmienna typu string, konwertowana jest na bity i wysyłana przez UDP do klienta
    void SendUDPData(std::string s);

    /// @brief Otwiera nasz serwer na otrzymywanie danych od klienta
    /// Używana jest metoda recv, która nie blokuje naszego socketu 
    /// @return Zwraca tablice char* z otrzymanymi danymi
    char* ReciveData();
};

