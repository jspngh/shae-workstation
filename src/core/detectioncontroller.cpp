#include "detectioncontroller.h"
#include "detection/detection/window_selection/SlidingWindow.h"
#include "detection/detection/detectors/HOG/HOGDetector.h"


DetectionController::DetectionController(QObject *parent):QObject(parent)
{

}

void DetectionController::addSequence(QString sequence)
{
    // this->sequencesQueue.push(sequence);
}

//void DetectionController::run()
//{
//    while(true){
//        // thread will go to sleep if there are no sequences to process
//        QString sequencePath = this->sequencesQueue.pop();
//        qDebug() << "Processing a sequence";
//    }
//}

