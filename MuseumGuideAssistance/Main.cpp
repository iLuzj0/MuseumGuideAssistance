// MuseumGuideAssistance.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "UDPSocketClient.h"
#include <iostream>
#include <string>
#include <fstream>
#include <JSON/json.hpp>
#include "OpenCVwrapper.h"

struct internalParameters
{
    double solverEps;
    int solverMaxIters;
    bool fastSolving;
    double filterAlpha;

    internalParameters()
    {
        solverEps = 1e-7;
        solverMaxIters = 50;
        fastSolving = true;
        filterAlpha = 0.1;
    }
};

int main(int argc, char* argv[])
{
    OpenCVwrapper imageProcessor;
    nlohmann::json ImageInfo;

    UDPSocket myUDPConnection("192.168.1.255", 3002, 3010);
    bool needBrodcasting = true;
    cv::VideoCapture cap; //
    std::string recIP;
    std::ifstream i("file.json");
    i >> ImageInfo;
    while (needBrodcasting) {
        char* data = myUDPConnection.ReciveData();
        
        if (data[0] != (char) 0) {
            std::cout << data;
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
                        myUDPConnection.SendUDPData(line);
                        IPFile.close();
                    }
                }
            }
        }
    }

    cap.open("http://"+recIP+":8080/video");
    //cap.open("http://192.168.1.172:8080/video");
    if (!cap.isOpened())  // if not success, exit program
    {
        std::cout << "Cannot open the video cam" << std::endl;
        return -1;
    }

    double dWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    double dHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

    int frameNum = 0;

    //Main app loop
    while (1)
    {
        char* data = myUDPConnection.ReciveData();
        cv::Mat frame;
        frameNum++;


        bool bSuccess = cap.read(frame); // read a new frame from video

        //if not success, break loop
        if (!bSuccess)  {
            std::cout << "Cannot read a frame from video stream" << std::endl;
            break;
        }

        else {
            if (data[0] == 't') {
                std::string ID = ImageInfo["ID"];
                std::cout << ID;
                if (ID == std::to_string(imageProcessor.FindApriltags(frame))) {
                    myUDPConnection.SendUDPData(nlohmann::to_string(ImageInfo));
                }
                else myUDPConnection.SendUDPData("");
            }
        }
    }
    return 0;
}
