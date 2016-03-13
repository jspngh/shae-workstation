#include "detectioncontroller.h"



DetectionController::DetectionController(QObject *parent):QObject(parent)
{

}

void DetectionController::addSequence(QString sequence)
{
    this->sequencesQueue.push(sequence);
}

void DetectionController::startProcessing()
{
    while(true){
        // thread will go to sleep if there are no sequences to process
        QString sequencePath = this->sequencesQueue.pop();
        std::cout << "Processing a sequence" << std::endl;
        emit this->newDetection();
    }
}

