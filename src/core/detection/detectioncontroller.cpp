#include "detectioncontroller.h"



DetectionController::DetectionController(QObject *parent):QObject(parent)
{

}

void DetectionController::processSequence(QString seq){
    // process a sequence
    std::cout << "Processing a sequence in thr: " << QThread::currentThreadId() << std::endl;

    this->manager.process(seq.toStdString());

    // once the sequence has processed the sequence emit the signal
    emit this->newDetection();
}
