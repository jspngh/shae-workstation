#include "detectioncontroller.h"
#include "detection/detection/window_selection/SlidingWindow.h"
#include "detection/detection/detectors/HOG/HOGDetector.h"
#include <QtDebug>


DetectionController::DetectionController(QObject *parent):QObject(parent)
{
  //  this->detector = new HOGDetector();
  //  this->wndSelector = new SlidingWindow(720, 1280, 190, 100, 300, 50, 150,20, 20);
  //  this->manager = DetectorManager(this->detector, this->wndSelector);
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

