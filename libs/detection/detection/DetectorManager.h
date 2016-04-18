#ifndef DETECTORMANAGER_H_
#define DETECTORMANAGER_H_

#include "DetectionList.h"
#include "window_selection/WindowSelection.h"
#include "detectors/Detector.h"
#include "../utils/DrawUtils.h"
#include "../core/FrameFromVideo.h"
#include "suppression/NonMaximumSuppression.h"
#include "detectors/HOG/HOGDetector.h"
#include "detectors/ACF/ACFDetector.h"
#include "window_selection/SlidingWindow.h"
#include <utils/GeoUtils.h>

#include <opencv2/opencv.hpp>
#include <iostream>
/*
 * DetectorManager is a builder/Broker class
 * It will chain the output of a WindowSelection object to a detector
 */
class DetectorManager
{
public:
    /*!
     * No-args (default) constructor
     * \brief Initialises a default DetectorManager
     * */
    DetectorManager(int fps);

    /*!
     * Constructor
     * \brief DetectorManager can be initialized with the desired detector and window selection routines
     * \param[in] fps Rate on which the sequence will be processed
     * */
    DetectorManager(Detector *det, WindowSelection *wndSel, int fps);
    ~DetectorManager();

    // setters
    void setDetector(Detector *detector);
    void setWindowSelection(WindowSelection *windowSelection);


    // getters
    Detector *getDetector()
    {
        return this->detector;
    }

    WindowSelection *getWindowSelector()
    {
        return this->windowSelection;
    }

    /*!
     * \brief Searches for human presence in a frame
     * \param frame The complete frame that will be searched for human presence
     * Note: the dimension of the frame must be equal to the dimension set in the WindowSelection object
     */
    DetectionList applyDetector(cv::Mat &frame);
    std::string getDetectorType();
    DetectionList process(std::string seq);
    std::vector<std::pair<double, double>> calculatePositions(DetectionList dl, std::pair<double, double> location, std::vector<vector<double>> xLUT, std::vector<vector<double>> yLUT, double orientation);

private:
    Detector *detector;
    WindowSelection *windowSelection;
    int fps; //< Frames per second on which the sequence will be analysed
    std::pair<double, double> derivePositionFromLUT(Detection d, std::vector<vector<double>> xLUT, std::vector<vector<double>> yLUT);
    cv::VideoWriter videoDetection;
};

#endif /* DETECTORMANAGER_H_ */
