// MuseumGuideAssistance.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "UDPSocketClient.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include "SQLWrapper.h"
#include <JSON/json.hpp>
#include "OpenCVwrapper.h"

bool needBrodcasting = true;

int main(int argc, char* argv[])
{
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
    std::cin >> SQLserver ;

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
    std::ifstream i("file.json");
    i >> ImageInfo;
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
            const char* search0;      // search pattern
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
    //cap.open("http://192.168.1.172:8080/video");

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
                        myUDPConnection.SendUDPData(nlohmann::to_string(mySQLServer.SQLGetExibitsIntoJSON("exibits", std::to_string(tagID))));
                    }
                }
                else myUDPConnection.SendUDPData("");
            }
        }
    }
    return 0;
}
