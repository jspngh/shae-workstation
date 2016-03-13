#ifndef _H_HOGDETECTOR
#define _H_HOGDETECTOR

#include <vector>
#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>

#include "../Detector.h"
#include "../../DetectionList.h"

/*!
 * \brief The HOGDetector class implements the Detector 'interface'
 * The detector relies on the openCV HOG + SVM detector to make detections.
 */

class HOGDetector: public Detector {
public:
    HOGDetector();
    std::string getName() const { return "HOG"; }

    bool applyDetectorOnWindow(const cv::Mat &Frame) const;
    DetectionList applyDetectorOnBand(const cv::Mat &Frame) const;
    DetectionList applyDetectorOnFrame(const cv::Mat &Frame) const;

    std::string getType() const;
    void setType(std::string type);
private:
    cv::HOGDescriptor hog;
};


#endif
