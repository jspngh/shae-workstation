#ifndef DETECTION_FRAMEPRODUCER_H
#define DETECTION_FRAMEPRODUCER_H

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <string>

<<<<<<< HEAD
// Virtual base class (Interface) for classes producing frames
class FrameProducer {
=======
// Class to inherit from by classes that return a frame (from directory, camera, network, ...)
class FrameProducer
{
>>>>>>> fe6385d11e0833c15a4b907450e23216fa34965a
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
