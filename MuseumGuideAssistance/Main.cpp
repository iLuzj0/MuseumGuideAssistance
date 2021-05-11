// MuseumGuideAssistance.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "UDPSocketClient.h"
#include <iostream>
#include "OpenCVwrapper.h"
#include "CameraCalibration.h"

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
    CameraCalibration cameraCalibration = CameraCalibration::CameraCalibration();
    UDPSocket myUDPConnection("192.168.1.172", 3002, 3010);

    cv::VideoCapture cap; //
    cv::TermCriteria solverTermCrit = cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS,
        30, 0.001);
    cv::Mat perViewErrors;
    cv::Mat cameraMat;
    cv::Mat distMat;
    cv::Mat stdDeviations;

    cap.open("http://192.168.1.172:8080/video");
    if (!cap.isOpened())  // if not success, exit program
    {
        std::cout << "Cannot open the video cam" << std::endl;
        return -1;
    }

    double dWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    double dHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

    std::cout << "Frame size : " << dWidth << " x " << dHeight << std::endl;

    int frameNum = 0;

    cv::namedWindow("CapturedFrame", cv::WINDOW_AUTOSIZE); //create a window called "MyVideo"
    cv::namedWindow("TagsFound", cv::WINDOW_AUTOSIZE);
    cv::moveWindow("TagsFound", 1000, 600);
    cv::moveWindow("CapturedFrame", 180, 600);

    while (1)
    {
        cv::Mat frame;
        frameNum++;

        char* data = myUDPConnection.ReciveData();

        if (data[0] == '0') {
            std::cout << "Recived data about image.";
        }

        bool bSuccess = cap.read(frame); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
            std::cout << "Cannot read a frame from video stream" << std::endl;
            break;
        }
        
        cv::imshow("CapturedFrame", frame); //show the frame in "MyVideo" window
        if (frameNum % 6 == 0) {
            cv::imshow("TagsFound", imageProcessor.FindApriltags(frame)); //show the frame in "MyVideo" window
            cameraCalibration.createInputImages(frame, frameNum);
        }
        if(cv::waitKey(1)>=0) break;
    }
    return 0;
}
