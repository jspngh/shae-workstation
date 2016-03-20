#include "detectioncontroller.h"

using namespace std;

DetectionController::DetectionController(Mediator *mediator, double fps, QString sequence, QObject *parent)
    : QThread(parent)
{
    this->fps = fps;
    this->sequence = sequence;
}

void DetectionController::run()
{
    this->streaming = true;
    // process a sequence
    cv::Mat frame;
    cv::VideoCapture capture = cv::VideoCapture(this->sequence.toStdString());
    if(capture.isOpened()){
    int numFrames = capture.get(CV_CAP_PROP_FRAME_COUNT);
    int iteratorFrames = 0;
    double fpsOriginal = (double) capture.get(CV_CAP_PROP_FPS);
    // frameHop is the number of frames that need to be skipped to process the sequence at the desired fps
    this->frameHop = fpsOriginal / (double) this->fps;
    do
    {
        //allow for frames to buffer
        QThread::sleep(1);       //check if new frames have arrived
        numFrames = capture.get(CV_CAP_PROP_FRAME_COUNT);
        while(iteratorFrames < numFrames)
        {
            numFrames = capture.get(CV_CAP_PROP_FRAME_COUNT);
            capture.set(CV_CAP_PROP_POS_FRAMES, iteratorFrames);
            capture >> frame;
            iteratorFrames += this->frameHop;
            DetectionList detectionList = this->manager.applyDetector(frame);
            QGeoCoordinate frameLocation;
            vector<pair<double,double>> locations = this->manager.calculatePositions(detectionList, pair<double,double>(frameLocation.longitude(),frameLocation.latitude()));
            for(int i = 0; i < detectionList.getSize(); i++){
                emit this->newDetection(DetectionResult(QGeoCoordinate(locations[i].first,locations[i].second),1));
                nrDetections++;
            }

        }

    }while(this->streaming);
    emit this->detectionFinished();

    }
 }

void DetectionController::streamFinished(){
    this->streaming = false;
}


int DetectionController::getNrDetections(){
    return this->nrDetections;
}

