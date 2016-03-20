#include "detectioncontroller.h"

using namespace std;

DetectionController::DetectionController(Mediator *mediator, double fps, QObject *parent)
    : QObject(parent)
{
    this->fps = fps;
    this->streaming = true;

}

void DetectionController::onProcessSequence(QString seq)
{
    std::cout << "onprocessequence started" << std::endl;
    // process a sequence
    cv::Mat frame;
    cv::VideoCapture capture = cv::VideoCapture(seq.toStdString());
    if(capture.isOpened()){
    int numFrames = capture.get(CV_CAP_PROP_FRAME_COUNT);
    int iteratorFrames = 0;
    double fpsOriginal = (double) capture.get(CV_CAP_PROP_FPS);
    // frameHop is the number of frames that need to be skipped to process the sequence at the desired fps
    this->frameHop = fpsOriginal / (double) this->fps;
    do
    {
        //allow for frames to buffer
        std::this_thread::sleep_for (std::chrono::seconds(1));
        //check if new frames have arrived
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
            }

        }
    }while(this->streaming);
    }

}

void DetectionController::onFinish(){
    std::cout << "onfinish started" << std::endl;

    this->streaming = false;
}

