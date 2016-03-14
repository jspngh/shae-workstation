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
     * No-args (default) constructor
     * \brief Initialises a default DetectorManager
     * */
    DetectorManager();

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
    Detector* getDetector(){
        return this->detector;
    }

    WindowSelection* getWindowSelector(){
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


private:
    Detector *detector;
    WindowSelection *windowSelection;
    int fps; //< Frames per second on which the sequence will be analysed
};

#endif /* DETECTORMANAGER_H_ */
