#include "detectioncontroller.h"



DetectionController::DetectionController(QObject *parent): QObject(parent)
{

}

void DetectionController::processSequence(QString seq)
{
    // process a sequence
    std::cout << "Processing a sequence in thr: " << QThread::currentThreadId() << std::endl;
    cv::Mat frame;
    DetectionList dl = this->manager.applyDetector(frame);
    //request locationFrame from persistence
    std::tuple<double,double> locationFrame;
    std:vector<std::tuple<double,double>> positions = this->manager.calculatePositions(dl, locationFrame);
    //
    // once the sequence has processed the sequence emit the signal
    for(int i = 0; i < positions.size(); i++){
        emit this->newDetection();
    }

}
