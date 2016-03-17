
#ifndef DETECTION_FRAMEFROMVIDEO_H
#define DETECTION_FRAMEFROMVIDEO_H

#include "FrameProducer.h"

<<<<<<< HEAD
/*!
 * \brief The FrameFromVideo class implements the virtual functions from FrameProducer
 * The class will provide frames at a specific fps from a sequence stored on disk
 */

class FrameFromVideo: public FrameProducer {
=======
class FrameFromVideo: public FrameProducer
{
>>>>>>> fe6385d11e0833c15a4b907450e23216fa34965a
public:
    FrameFromVideo(std::string directory, int fps);
    virtual ~FrameFromVideo();

    /*!
     * \brief giveFrame
     * \return The frame to process.
     * NOTE: first check if there is a frame to process (e.g. if the sequence has ended no frame is available anymore).
     * Check this condition using the frameAvailable() function
     */
    cv::Mat giveFrame();

<<<<<<< HEAD
    bool frameAvailable();

=======
    std::string getFilename()
    {
        return "video";
    }
>>>>>>> fe6385d11e0833c15a4b907450e23216fa34965a
private:
    cv::VideoCapture capture;
    int fps; //!< Desired fps
    double numFrames;
    double fpsOriginal; //!< The original fps
    double frameHop; //!< frameHop is the number of frames that need to be skipped to process the sequence at the desired fps
    double currentFrame;
};

#endif /* DETECTION_FRAMEFROMVIDEO_H */
