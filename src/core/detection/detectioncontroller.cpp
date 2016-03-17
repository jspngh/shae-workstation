#include "detectioncontroller.h"



DetectionController::DetectionController(QObject *parent, double fps): QObject(parent)
{
    this->fps = fps;

}

void DetectionController::processSequence(QString seq)
{

    // process a sequence
    cv::Mat frame;
    cv::VideoCapture capture = cv::VideoCapture(seq.toStdString());
    if(capture.isOpened()){
    int numFrames = capture.get(CV_CAP_PROP_FRAME_COUNT);
    int iteratorFrames = 0;
    double fpsOriginal = (double) capture.get(CV_CAP_PROP_FPS);
    // frameHop is the number of frames that need to be skipped to process the sequence at the desired fps
    this->frameHop = fpsOriginal / (double) this->fps;

    while(iteratorFrames < numFrames)
    {
        numFrames = capture.get(CV_CAP_PROP_FRAME_COUNT);
        capture.set(CV_CAP_PROP_POS_FRAMES, iteratorFrames);
        capture >> frame;
        iteratorFrames += this->frameHop;
        DetectionList dl = this->manager.applyDetector(frame);
        for(int i = 0; i < dl.getSize(); i++){
            emit this->newDetection();
        }
    }
    //request locationFrame from persistence
    //std::tuple<double,double> locationFrame;
    //std:vector<std::tuple<double,double>> positions = this->manager.calculatePositions(dl, locat}ionFrame);
    //
    // once the sequence has processed the sequence emit the signal
    }

}
