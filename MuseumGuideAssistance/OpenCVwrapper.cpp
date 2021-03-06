#include "OpenCVwrapper.h"

/// @brief Konstruktor towrzący klasę TagFamily na podstawie podanej rodziny AprilTagów
/// @param family Rodzina używanych AprilTagów domyślnie ustawiona jest najpopularniejsza rodzina to jest: Tag36h11
TagFamily tagfamily(DEFAULT_TAG_FAMILY);

/// @brief Konstruktor tworzący klasę TagDetector na podstawie wcześniej utworzonej rodziny
/// @param TagFamily Przyjmuje klasę TagFamily na podstawie której tworzy ustawienia dla detekcji AprilTagów
TagDetector tagdetector(tagfamily);

int OpenCVwrapper::FindApriltags(cv::Mat InputImage)
{
    opticalCenter.x = InputImage.cols * 0.5;
    opticalCenter.y = InputImage.rows * 0.5;
    int tagID;
    clock_t start = clock();

    tagdetector.process(InputImage, opticalCenter, detections);

    clock_t end = clock();

    //Debug cout
    std::cout << std::endl;
    std::cout << "Got " << detections.size() << " detections in " << double(end - start) / CLOCKS_PER_SEC << " seconds.\n";

    cv::Mat img = tagfamily.superimposeDetections(InputImage, detections);
    if (detections.size() > 0) {
        for (size_t i = 0; i < detections.size(); ++i) {
            const TagDetection& d = detections[i];
            cv::putText(img, std::to_string(d.id), d.cxy, cv::FONT_ITALIC, 1.5, cv::Scalar(0, 0, 255), 3);
            tagID = d.id;
        }
        return tagID;
    }
    else return 2137;
}