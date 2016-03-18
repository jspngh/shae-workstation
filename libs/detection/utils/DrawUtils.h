//
// Created by lars on 3/1/16.
//

#ifndef DETECTION_DRAWUTILS_H
#define DETECTION_DRAWUTILS_H

#include <opencv2/opencv.hpp>
#include "../detection/DetectionList.h"

using namespace std;

#define COLOR_WHITE 0
#define COLOR_RED 1
#define COLOR_GREEN 2
#define COLOR_BLUE 3

void drawDetectionLists(std::vector<DetectionList> L1, std::vector<cv::Scalar> colour, cv::Mat frame, int waitKeyEvent);
void drawRectOnFrame(const cv::Mat &frame, const cv::Rect &rect, const int color, int waitKeyEvent);

#endif //DETECTION_DRAWUTILS_H
