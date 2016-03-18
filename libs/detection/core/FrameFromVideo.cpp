#include "FrameFromVideo.h"


FrameFromVideo::FrameFromVideo(std::string sequence, int fps) {
    this->capture = cv::VideoCapture(sequence);
    this->fps = fps;

    this->numFrames = capture.get(CV_CAP_PROP_FRAME_COUNT);
    this->fpsOriginal = (double) capture.get(CV_CAP_PROP_FPS);
    // frameHop is the number of frames that need to be skipped to process the sequence at the desired fps
    this->frameHop = fpsOriginal / (double) this->fps;
    this->currentFrame = 0.0;
}


FrameFromVideo::~FrameFromVideo() {}

cv::Mat FrameFromVideo::giveFrame() {
    cv::Mat frame;
    capture.set(CV_CAP_PROP_POS_FRAMES, currentFrame);
    capture >> frame;
    currentFrame += frameHop;
    return frame;
}

bool FrameFromVideo::frameAvailable() {
    return this->currentFrame < this->numFrames;
}
