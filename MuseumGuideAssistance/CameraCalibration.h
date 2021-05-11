#pragma once
  
#include <vector>
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/highgui/highgui.hpp>

class CameraCalibration
{
	std::string filePath = "calibrationImages";
	std::vector<std::vector<cv::Point3f>> objectPoints;
	std::vector<std::vector<cv::Point2f>> imagePoints;
	cv::Mat cameraMatrix;
	cv::Mat distCoeffs;
	cv::Mat map1, map2;

public:
	CameraCalibration();
	void createInputImages(cv::Mat inputFrame,int frameCount);
	//int addChessboardPoints(const std::vector<std::string>& filelist, cv::Size& boardSize);
	//void addPoints(const std::vector<cv::Point2f>& imageCorners, const std::vector<cv::Point3f>& objectCorners);
	//double calibrate(cv::Size& imageSize);
	//void setCalibrationFlag(bool radial8CoeffEnabled = false, bool tangentialParamEnabled = false);
	//cv::Mat cameraCalibrationRemap(const cv::Mat& image);
	//cv::Mat getCameraMatrix() { return cameraMatrix; }
	//cv::Mat getDistCoeffs() { return distCoeffs; }
};

