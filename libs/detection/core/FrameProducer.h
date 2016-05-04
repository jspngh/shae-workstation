#ifndef DETECTION_FRAMEPRODUCER_H
#define DETECTION_FRAMEPRODUCER_H

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <string>

// Virtual base class (Interface) for classes producing frames
class FrameProducer
{
public:
    FrameProducer();
    virtual ~FrameProducer();

    /*!
     * \brief giveFrame
     * \return The frame to process
     */
    virtual cv::Mat giveFrame() = 0;

    /*!
     * \brief frameAvailable
     * \return return true if there is a frame to process, otherwise false
     */
    virtual bool frameAvailable() = 0;

};

#endif /* DETECTION_FRAMEPRODUCER_H */
