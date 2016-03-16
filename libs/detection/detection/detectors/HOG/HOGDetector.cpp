#include "HOGDetector.h"

#include <iostream>

HOGDetector::HOGDetector()
{
    // set the default OpenCV PeopleDetector (note: this detector works on frames of size 64 x 128)
    this->hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
    this->type = "windows";
}

std::string HOGDetector::getType() const
{
    return type;
}


bool HOGDetector::applyDetectorOnWindow(const cv::Mat &roi) const
{
    cv::Mat window;
    // resize the roi to the window size of the detector
    cv::resize(roi, window, cv::Size(64, 128));
    std::vector<cv::Point> found;
    // TODO: step size and padding can be altered (tests need to be conducted)
    hog.detect(window, found, 0, cv::Size(4, 4), cv::Size(20, 20));

    // if found is not empty, a person was detected in the roi.
    return !found.empty();
}
DetectionList HOGDetector::applyDetectorOnFrame(const cv::Mat &Frame) const
{
    return applyDetectorOnBand(Frame);
}

DetectionList HOGDetector::applyDetectorOnBand(const cv::Mat &Frame) const
{
    DetectionList DL;

    float Upscale = 1.0;

    cv::Mat U;
    cv::resize(Frame, U, cv::Size(), Upscale, Upscale);

    std::vector<cv::Rect> found;

    std::vector<double> Scores;
    hog.detectMultiScale(U, found, Scores, 0, cv::Size(8, 8), cv::Size(32, 32), 1.1, 0);


    for (int i = 0; i < found.size(); i++) {
        cv::Rect r = found[i];
        // the HOG detector returns slightly larger rectangles than the real objects.
        // so we slightly shrink the rectangles to get a nicer output.
        r.x += cvRound(r.width * 0.1);
        r.width = cvRound(r.width * 0.8);
        r.y += cvRound(r.height * 0.07);
        r.height = cvRound(r.height * 0.8);
        if (Scores[i] >= 1)
            DL.addDetection(r.x, r.y, r.width, r.height, Scores[i], this->getName());
    }

    DL.resizeDetections(Upscale);

    return DL;
}


void HOGDetector::setType(std::string type)
{
    this->type = type;
}
