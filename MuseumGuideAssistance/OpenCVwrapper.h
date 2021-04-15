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

typedef struct TagTestOptions {

    TagTestOptions() :
        show_debug_info(false),
        show_timing(false),
        show_results(false),
        be_verbose(false),
        no_images(false),
        generate_output_files(false),
        params(),
        family_str(DEFAULT_TAG_FAMILY),
        error_fraction(1) {
    }
    bool show_debug_info;
    bool show_timing;
    bool show_results;
    bool be_verbose;
    bool no_images;
    bool generate_output_files;
    TagDetectorParams params;
    std::string family_str;
    double error_fraction;
} TagTestOptions;

class OpenCVwrapper
{
public:
    cv::Mat FindApriltags(cv::Mat InputImage);

private:
    cv::Point2d opticalCenter;
    TagDetectionArray detectionsleft;
    nlohmann::json CamParams;
};