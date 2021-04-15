/*********************************************************************
 * This file is distributed as part of the C++ port of the APRIL tags
 * library. The code is licensed under GPLv2.
 *
 * Original author: Edwin Olson <ebolson@umich.edu>
 * C++ port and modifications: Matt Zucker <mzucker1@swarthmore.edu>
 ********************************************************************/

#include <cstdio>
#include <iostream>
#include <getopt.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "TagDetector.h"
#include "DebugImage.h"

#define DEFAULT_TAG_FAMILY "Tag36h11"

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
      error_fraction(1){
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

TagTestOptions parse_options() {

    TagTestOptions opts;

    opts.show_debug_info = true;
    opts.show_timing = true;
    opts.show_results = true;
    opts.be_verbose = true;
    opts.no_images = false;
    opts.generate_output_files = true;
    opts.params.segDecimate = true;
    opts.params.sigma = 0;
    opts.params.segSigma = 0;
    opts.params.thetaThresh = 0;
    opts.params.magThresh = 0;
    opts.params.adaptiveThresholdValue = 0;
    opts.params.adaptiveThresholdRadius = 0;
    opts.params.refineBad = true;
    opts.params.refineQuads = true;
    opts.params.newQuadAlgorithm = true;
    opts.family_str = DEFAULT_TAG_FAMILY;
    opts.error_fraction = -10;

    opts.params.adaptiveThresholdRadius += (opts.params.adaptiveThresholdRadius+1) % 2;
        if (opts.be_verbose) {
            opts.show_debug_info = opts.show_timing = opts.show_results = true;
        }
    return opts;
}

int main(int argc, char** argv) {

  TagFamily family(DEFAULT_TAG_FAMILY);

  TagDetector detector(family);

  TagDetectionArray detections;

  cv::Mat src = cv::imread("C:/Users/pawel/Desktop/Image.jpg");

  while (std::max(src.rows, src.cols) > 1920) {
      cv::Mat tmp;
      cv::resize(src, tmp, cv::Size(0,0), 0.5, 0.5);
      src = tmp;
    }
    cv::Point2d opticalCenter(0.5*src.rows, 0.5*src.cols);

    clock_t start = clock();
    detector.process(src, opticalCenter, detections);
    clock_t end = clock();

    std::cout << "Got " << detections.size() << " detections in "
              << double(end-start)/CLOCKS_PER_SEC << " seconds.\n";

      for (size_t i=0; i<detections.size(); ++i) {
        const TagDetection& d = detections[i];
        std::cout << " - Detection: id = " << d.id << ", "
                  << "code = " << d.code << ", "
                  << "rotation = " << d.rotation << "\n";
      }
  cv::Mat img = family.superimposeDetections(src, detections);
  labelAndWaitForKey("LOL", "Detected", img, ScaleNone, true);
  return 0;
}
