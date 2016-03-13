#ifndef DETECTIONCONTROLLER_H
#define DETECTIONCONTROLLER_H

#include <QString>
#include <QDebug>
#include <QObject>
#include <iostream>

#include "utils/queue.h"
#include "detection/detection/DetectorManager.h"

class DetectionController : public QObject
{
    Q_OBJECT

public:
    DetectionController(QObject *parent=0);
    ~DetectionController(){}

public slots:
    void startProcessing();
    void addSequence(QString sequenceName);

signals:
    void newDetection();

private:
    Queue sequencesQueue; //!< Thread safe queue containing the sequences that needs to be processed by the detector
    DetectorManager manager;
};

#endif // DETECTIONCONTROLLER_H
