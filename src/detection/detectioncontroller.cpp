#include "detectioncontroller.h"
#include <QThread>

DetectionController::DetectionController(Mediator *mediator, QObject *parent)
    : QObject(parent)
{
}

void DetectionController::processSequence(QString seq)
{
    // process a sequence
    qDebug() << "Processing a sequence in thr: " << QThread::currentThreadId();

    this->manager.process(seq.toStdString());

    // once the sequence has processed the sequence emit the signal
    emit this->newDetection();
}

