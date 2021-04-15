// MuseumGuideAssistance.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "OpenCVwrapper.h"

int main(int argc, char* argv[])
{
    OpenCVwrapper imageProcessor;
    cv::VideoCapture cap; //

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

        bool bSuccess = cap.read(frame); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
            std::cout << "Cannot read a frame from video stream" << std::endl;
            break;
        }
        
        cv::imshow("CapturedFrame", frame); //show the frame in "MyVideo" window
        if (frameNum % 6 == 0) {
            cv::imshow("TagsFound", imageProcessor.FindApriltags(frame)); //show the frame in "MyVideo" window
        }
        if(cv::waitKey(1)>=0) break;
    }
    return 0;
}