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

class DetectorManager {
public:
    /*!
     * Constructor
     * \brief Initialises a DetectorManager with the desired Detector and WindowSelection
     * */
    DetectorManager(Detector *detector, WindowSelection *windowSelection);

    /*!
     * No-args (default) constructor will leave detector and windowSelection to NULL.
     * The members will have to be set via the appropriate setters.
     */
    DetectorManager();
    virtual ~DetectorManager();

    // setters
    void setDetector(Detector *detector);
    void setWindowSelection(WindowSelection *windowSelection);

    /*!
     * \brief Searches for human presence in a frame
     * \param frame The complete frame that will be searched for human presence
     * Note: the dimension of the frame must be equal to the dimension set in the WindowSelection object
     */
    DetectionList applyDetector(cv::Mat &frame);

private:
    Detector *detector;
    WindowSelection *windowSelection;
};

#endif /* DETECTORMANAGER_H_ */
