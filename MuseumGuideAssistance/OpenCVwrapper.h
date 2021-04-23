#include <iostream>
#include <vector>
#include <iomanip>
#include <list>
#include <fstream>

#include <JSON/json.hpp>
#include <cstdio>
#include <getopt.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/videoio.hpp>
#include "TagDetector.h"
#include "DebugImage.h"
#include "CameraUtil.h"
#define DEFAULT_TAG_FAMILY "Tag36h11"

#pragma once

class OpenCVwrapper
{
public:
    cv::Mat FindApriltags(cv::Mat InputImage);
    bool detectAndParseChessboard(const cv::Mat& frame);
    std::vector<std::vector<cv::Point2f> > imagePoints;
    std::vector< std::vector<cv::Point3f> > objectPoints;

private:
    cv::Point2d opticalCenter;
    TagDetectionArray detections;
    cv::Size mBoardSize = cv::Size(12, 8);
    float mSquareSize = 4.0;
    std::vector<cv::Point2f> mTemplateLocations;
    std::vector<cv::Point2f> mCurrentImagePoints;
};