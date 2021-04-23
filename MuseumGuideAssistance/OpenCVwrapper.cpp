#include "OpenCVwrapper.h"

TagFamily tagfamily(DEFAULT_TAG_FAMILY);
TagDetector tagdetector(tagfamily);

cv::Mat OpenCVwrapper::FindApriltags(cv::Mat InputImage)
{
    opticalCenter.x = InputImage.cols * 0.5;
    opticalCenter.y = InputImage.rows * 0.5;

    clock_t start = clock();

    tagdetector.process(InputImage, opticalCenter, detections);

    clock_t end = clock();

    //Debug cout
    std::cout << std::endl;
    std::cout << "Got " << detections.size() << " detections in " << double(end - start) / CLOCKS_PER_SEC << " seconds.\n";

    cv::Mat img = tagfamily.superimposeDetections(InputImage, detections);

    for (size_t i = 0; i < detections.size(); ++i) {
        const TagDetection& d = detections[i];
        cv::putText(img, std::to_string(d.id), d.cxy, cv::FONT_ITALIC, 1.5, cv::Scalar(0, 0, 255), 3);
        std::cout << " - Detection: " << "\n"
            << "\tid = " << d.id << "\n"
            << "\tTag center = " << d.cxy << "\n"
            << "\trotation = " << d.rotation << "\n\n";
    }
    return img;
}


bool OpenCVwrapper::detectAndParseChessboard(const cv::Mat& frame)
{
    std::vector<cv::Point3f> mobjectPoints;
    int chessBoardFlags = cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE | cv::CALIB_CB_FAST_CHECK;
    bool isTemplateFound = cv::findChessboardCorners(frame, mBoardSize, mCurrentImagePoints, chessBoardFlags);

    if (isTemplateFound) {
        cv::Mat viewGray;
        cv::cvtColor(frame, viewGray, cv::COLOR_BGR2GRAY);
        cv::cornerSubPix(viewGray, mCurrentImagePoints, cv::Size(11, 11),
            cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 30, 0.1));
        cv::drawChessboardCorners(frame, mBoardSize, cv::Mat(mCurrentImagePoints), isTemplateFound);
        mTemplateLocations.insert(mTemplateLocations.begin(), mCurrentImagePoints[0]);

        mobjectPoints.reserve(mBoardSize.height * mBoardSize.width);
        for (int i = 0; i < mBoardSize.height; ++i)
            for (int j = 0; j < mBoardSize.width; ++j)
                mobjectPoints.push_back(cv::Point3f(j * mSquareSize, i * mSquareSize, 0));
        imagePoints.push_back(mCurrentImagePoints);
        objectPoints.push_back(mobjectPoints);
    }
    return isTemplateFound;
}
