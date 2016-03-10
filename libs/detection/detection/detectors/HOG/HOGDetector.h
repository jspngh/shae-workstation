#ifndef _H_HOGDETECTOR
#define _H_HOGDETECTOR

#include <vector>
#include <string>
#include <iostream>

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
    DetectionList applyDetector(const cv::Mat &Frame) const;
private:
    cv::HOGDescriptor hog;
};


#endif
