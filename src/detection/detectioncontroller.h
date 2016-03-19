#ifndef DETECTIONCONTROLLER_H
#define DETECTIONCONTROLLER_H

#include <QString>
#include <QDebug>
#include <QObject>
#include "detection/DetectorManager.h"
#include "core/mediator.h"

class DetectionController : public QObject
{
    Q_OBJECT

public:
    DetectionController(Mediator *mediator, QObject *parent = 0);
    ~DetectionController() {}

public slots:
    void processSequence(QString seq);

signals:
    void newDetection();

private:
    DetectorManager manager;
};

#endif // DETECTIONCONTROLLER_H
