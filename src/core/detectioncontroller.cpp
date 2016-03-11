#include "detectioncontroller.h"
#include "../../libs/detection/detection/window_selection/SlidingWindow.h"
#include "../../libs/detection/detection/detectors/HOG/HOGDetector.h"
#include "../../libs/detection/detection/detectors/ACF/ACFDetector.h"
#include <QtDebug>


DetectionController::DetectionController()
{
    this->detector = ACFDetector();
    this->wndSelector = WindowSelection(720, 1280, 190, 100, 300, 50, 150,20, 20);
    this->manager = DetectorManager(&this->detector, &this->wndSelector);
}

DetectionController::addSequence(QString sequence)
{
    this->sequencesQueue.push(sequence);
}

DetectionController::run()
{
    while(true){
        // thread will go to sleep if there are no sequences to process
        QString sequencePath = this->sequencesQueue.pop();
        qDebug() << "Processing a sequence";
    }
}

