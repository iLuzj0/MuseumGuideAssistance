#include "CameraCalibration.h"

CameraCalibration::CameraCalibration() {
    int status = _mkdir(filePath.c_str());
    if (status == 0) {
        std::cout << "Dir has been created";
    }
    else if (status == -1) {
        std::cout << "Dir was already in place";
    }
    else {
        std::cout << "Could not create dir";
    }
}


void CameraCalibration::createInputImages(cv::Mat inputFrame, int frameCount) {
    cv::imwrite(filePath + "/clibImage" + std::to_string(frameCount)+".jpg", inputFrame);
}	
