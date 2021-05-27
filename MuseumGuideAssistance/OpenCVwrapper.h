#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/videoio.hpp>
#include "TagDetector.h"
#include "DebugImage.h"
#include "CameraUtil.h"

/// Makro definiujące domyślną rodzinę AprilTagów
#define DEFAULT_TAG_FAMILY "Tag36h11"

#pragma once
/// @brief Klasa, która zajmuje się wykrywaniem tagów przez serwer.
/// @author Dominik Tekiela
/// @date 27.05.2021
class OpenCVwrapper
{
public:
    /// @brief Odnajdywanie tagów na podstawie pobranego zdjecia
    /// Ze zdjęcia pozyskiwana jest wysokość i szerokość, następnie algorytm detekcji szuka na zdjęciu AprilTagów.
    /// Jeśli tag zostanie znaleziony, zwracane jest jego ID.
    /// Jeśli na zdjęciu znajduje sie więcej niż jeden tag (do czego nie powinno dojść), wtedy aplikacja zwraca tag o mniejszym ID.
    /// @param InputImage to matryca posiadajaca informacje na temat obrazu przesłanego z aplikacji Android
    /// @return Zwraca informacje - jaki tag został znaleziony przez system
    int FindApriltags(cv::Mat InputImage);

private:
    /// Punkt na ekranie - wektor 2D (szerokość zdj/wysokość zdj)
    cv::Point2d opticalCenter;

    /// Lista znalezionych tagów przez algorytm
    TagDetectionArray detections;
};