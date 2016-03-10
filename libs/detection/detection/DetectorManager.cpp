#include "DetectorManager.h"
#include "suppression/NonMaximumSuppression.h"

DetectorManager::DetectorManager(Detector *detector, WindowSelection *windowSelection) {
    this->detector = detector;
    this->windowSelection = windowSelection;
}

DetectorManager::DetectorManager() {}

DetectorManager::~DetectorManager() {
    // nothing needs to be deleted because nothing was created in the constructor
}

DetectionList DetectorManager::applyDetector(cv::Mat &frame) {
    DetectionList detections;
    cv::Rect win;
    cv::Mat roi;

    // as long as there is a next window we loop over the frame
    while(this->windowSelection->nextWindow(win)){
        // select the window from the complete frame
        roi = frame(win);
        // drawRectOnFrame(frame, win, COLOR_WHITE, 0);

        if(this->detector->applyDetectorOnWindow(roi)){
            // the detector detected a person in the roi
            // we add the detection to the list
            detections.addDetection(win.x, win.y, win.width, win.height, 1, this->detector->getName());
        }
    }
    // the sliding window needs to be reset after looping over a complete frame.
    this->windowSelection->reset();

    // do suppression of the results before return the detectionlist.
    // the suppression is done via the dollarNMS function provided in the NonMaximumSuppression class
    NonMaximumSuppression NMS;
    return NMS.dollarNMS(detections);
}

