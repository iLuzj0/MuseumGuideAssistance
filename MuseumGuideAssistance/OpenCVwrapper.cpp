#include "OpenCVwrapper.h"

TagFamily tagfamily(DEFAULT_TAG_FAMILY);
TagDetector tagdetector(tagfamily);

cv::Mat OpenCVwrapper::FindApriltags(cv::Mat InputImage)
{
    opticalCenter.x = InputImage.cols * 0.5;
    opticalCenter.y = InputImage.rows * 0.5;

    clock_t start = clock();

    tagdetector.process(InputImage, opticalCenter, detectionsleft);

    clock_t end = clock();

    //Debug cout
    std::cout << std::endl;
    std::cout << "Got " << detectionsleft.size() << " detections in " << double(end - start) / CLOCKS_PER_SEC << " seconds.\n";

    cv::Mat img = tagfamily.superimposeDetections(InputImage, detectionsleft);

    for (size_t i = 0; i < detectionsleft.size(); ++i) {
        const TagDetection& d = detectionsleft[i];
        cv::putText(img, std::to_string(d.id), d.cxy, cv::FONT_ITALIC, 1.5, cv::Scalar(0, 0, 255), 3);
        std::cout << " - Detection: " << "\n"
            << "\tid = " << d.id << "\n"
            << "\tTag center = " << d.cxy << "\n"
            << "\trotation = " << d.rotation << "\n\n";
    }
    return img;
}
