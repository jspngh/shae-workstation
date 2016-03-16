#ifndef DETECTORMANAGER_H_
#define DETECTORMANAGER_H_

#include "DetectionList.h"
#include "window_selection/WindowSelection.h"
#include "detectors/Detector.h"
#include "../utils/DrawUtils.h"

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
    DetectorManager();
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
    string getDetectorType();


private:
    Detector *detector;
    WindowSelection *windowSelection;
};

#endif /* DETECTORMANAGER_H_ */
