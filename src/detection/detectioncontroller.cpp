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

void DetectionController::setController(Controller *value)
{
    controller = value;
    controller->getMediator()->addSignal(this, (char*) SIGNAL(pathCalculated(Search *)), QString("pathCalculated(Search*)"));
    controller->getMediator()->addSlot(this, (char*) SLOT(onStartSearch(Search *)), QString("startSearch(Search*)"));
}
