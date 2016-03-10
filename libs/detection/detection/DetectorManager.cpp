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

string DetectorManager::getDetectorType() {
    return this->detector->getType();
}

void DetectorManager::setDetector(Detector *detector) {
    this->detector=detector;
}

void DetectorManager::setWindowSelection(WindowSelection *windowSelection) {
    this->windowSelection=windowSelection;
}



DetectionList DetectorManager::applyDetector(cv::Mat &frame) {
    DetectionList detections;
    NonMaximumSuppression NMS;
    if (this->detector->getType().compare("frame") == 0) {
        detections =  this->detector->applyDetectorOnFrame(frame);
        //use standardNMS as dollarNMS fails on the given detectionList from ACF
        if(detections.getSize()>0)
            detections = NMS.standardNMS(detections,0.2);
        return detections;
    }

    cv::Rect win;
    cv::Mat roi;

    // as long as there is a next window we loop over the frame
    while(this->windowSelection->nextWindow(win)) {
        // select the window from the complete frame
        roi = frame(win);
        //drawRectOnFrame(frame, win, COLOR_WHITE, 0);
        if (this->detector->getType().compare("window") == 0) {
            if (this->detector->applyDetectorOnWindow(roi)) {
                // the detector detected a person in the roi
                // we add the detection to the list
                detections.addDetection(win.x, win.y, win.width, win.height, 1, this->detector->getName());
            }
        }
        if (this->detector->getType().compare("band") == 0) {
            DetectionList DL = this->detector->applyDetectorOnBand(roi);
            for(int i= 0; i< DL.getSize(); i++){
                Detection D = DL.returnDetections()[i];
                detections.addDetection(D.getX(),D.getY()+win.y,D.getWidth(),D.getHeight(),1,this->detector->getName());
            }
        }

        if (this->detector->getType().compare("frame") == 0) {
            detections = this->detector->applyDetectorOnFrame(roi);
        }
    }



    // the sliding window needs to be reset after looping over a complete frame.
    this->windowSelection->reset();

    // do suppression of the results before return the detectionlist.
    // the suppression is done via the dollarNMS function provided in the NonMaximumSuppression class
    if(detections.getSize()>0)
        detections = NMS.standardNMS(detections,0.2);
    return detections;
}



