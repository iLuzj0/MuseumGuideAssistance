#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <JSON/json.hpp>
#include "UDPSocketClient.h"
#include "SQLWrapper.h"
#include "OpenCVwrapper.h"

/// @brief Parametr do określenia czy powinniśmy w danym czasię słać dane po adresie broadcast, zmienia swoją wartość, gdy otwrzymamy odpowiedź od klienta posługującego sie aplikacją na systemie Android
bool needBrodcasting = true;

/// @brief Główna funkcja prowadząca całość operacji na serwerze. 
/// Po włączeniu programu musimy podać wszystkie potrzebne dane, do tego aby nasz serwer mógł prawidłowo działać.
/// Następnie łączymy się z bazą danych postępując zgodnie z komunikatami które zostają wypisane w ekranie konsoli.
/// Program wchodzi w stan bradcastingu - czeka na odpowiedź klienta używającego aplikacji na systemie Android.
/// Po połączeniu się z Androidem następuje przesył danych - obraz tworzony podczas robienia zdjęcia w aplikacji jest przetwarzany przez algorytm wyszykiwania tagów.
/// Po odnalezieniu tagów do Androida zwracana jest wartość JSON która definiuje czego zdjęcie zrobiliśmy.
/// @return Zwraca 0 przy zakończeniu programu, jeśli wystąpi jakiś problem, program zwróci -1
/// @author Dominik Tekiela
/// @date 27.05.2021
int main() {
    std::cout << "Welcome to Museum Guide Assistance server !" << std::endl;
    std::string broadcastIp;
    std::cout << "Let me know your broadcast IP: ";
    std::cin >> broadcastIp;
    std::string SQLserver;
    std::string SQLuser;
    std::string SQLpasswd;
    std::string SQLdatabase;
    int port = 3306;

    system("CLS");

    std::cout << "Podaj dane do mySQL:" << std::endl;
    std::cout << "Server: ";
    std::cin >> SQLserver;

    std::cout << "\nUser: ";
    std::cin >> SQLuser;

    std::cout << "\nPassword: ";
    std::cin >> SQLpasswd;

    std::cout << "\nDatabase: ";
    std::cin >> SQLdatabase;

    std::cout << "\nPort: ";
    std::cin >> port;

    SQLWrapper mySQLServer(SQLserver.c_str(), SQLuser.c_str(), SQLpasswd.c_str(), SQLdatabase.c_str(), port);

    system("PAUSE");

    OpenCVwrapper imageProcessor;
    nlohmann::json ImageInfo;
    UDPSocket myUDPConnection(broadcastIp.c_str(), 3002, 3010);
    
    std::string recIP;
    
    system("CLS");

    std::cout << "Started broadcasting on " << broadcastIp << std::endl;

    while (needBrodcasting) {
        char* data = myUDPConnection.ReciveData();
        
        if (data[0] != (char) 0) {
            recIP = data;
            needBrodcasting = false;
        }

        if (needBrodcasting) {
            std::string line;
            std::ifstream IPFile;
            int offset;
            const char* search0;// search pattern
            search0 = "IPv4 Address. . . . . . . . . . . :";
            system("ipconfig > ip.txt");

            IPFile.open("ip.txt");
            if (IPFile.is_open())
            {
                while (!IPFile.eof())
                {
                    std::getline(IPFile, line);
                    if ((offset = line.find(search0, 0)) != std::string::npos)
                    {
                        line.erase(0, 39);
                        system("CLS");
                        myUDPConnection.SendUDPData(line);
                        std::cout << "Waiting for response from host";
                        IPFile.close();
                    }
                }
            }
        }
    }

    system("CLS");

    std::cout << "IP found ! : " << recIP << std::endl;

    cv::VideoCapture cap; //

    cap.open("http://"+recIP+":8080/video");
    //vintage cap.open("http://192.168.1.172:8080/video");

    if (!cap.isOpened())  // if not success, exit program
    {
        std::cout << "Cannot open the video cam" << std::endl;
        return -1;
    }

    std::cout << "Video capture started." << std::endl;

    double dWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    double dHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

    //Main app loop
    while (1)
    {
        char* data = myUDPConnection.ReciveData();
        cv::Mat frame;


        bool bSuccess = cap.read(frame); // read a new frame from video

        //if not success, break loop
        if (!bSuccess)  {
            std::cout << "Cannot read a frame from video stream" << std::endl;
            break;
        }

        else {
            if (data[0] == 't') {
                int tagID = imageProcessor.FindApriltags(frame);
                if (tagID != 2137) {
                    if (tagID == 0 || tagID == 10 || tagID == 20) {
                        myUDPConnection.SendUDPData(nlohmann::to_string(mySQLServer.SQLGetExitsInfo(std::to_string(tagID))));
                    }
                    else {
                        myUDPConnection.SendUDPData(nlohmann::to_string(mySQLServer.SQLGetExibitsIntoJSON(std::to_string(tagID))));
                    }
                }
                else myUDPConnection.SendUDPData("");
            }
        }
    }
    return 0;
}
