#ifndef DETECTOR_H
#define DETECTOR_H

#include <iostream>
#include <string>
#include <vector>
#include "../DetectionList.h"


/*!
	Defines the 'interface' of an Detector
*/
class Detector
{
public:
    Detector() {}
    ~Detector() {}

    /*!
     * \brief Return true if a person is detected on the frame
     * Note: don't pass a complete frame to the method, at most 1 person can be detected.
     * \param roi Region Of Interest: in most cases a subframe of the complete frame
     */
    virtual bool applyDetectorOnWindow(const cv::Mat &roi) const = 0;

    /*!
     * \brief Returns a list of detections. The complete band is searched for human presence.
     */
    virtual DetectionList applyDetectorOnBand(const cv::Mat &frame) const = 0;
    virtual DetectionList applyDetectorOnFrame(const cv::Mat &frame) const = 0;

    /*!
     * \brief Return the name of the detector
     */
    virtual std::string getName() const = 0;

    virtual std::string getType() const = 0;
    virtual void setType(std::string type) = 0;
protected:
    std::string type;

};
#endif // DETECTOR_H
