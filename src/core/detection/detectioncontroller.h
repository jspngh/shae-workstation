#ifndef DETECTIONCONTROLLER_H
#define DETECTIONCONTROLLER_H

#include <QString>
#include <QDebug>
#include <QObject>
#include <QThread>
#include <iostream>

#include "detection/detection/DetectorManager.h"

class DetectionController : public QObject
{
    Q_OBJECT

public:
    DetectionController(QObject *parent = 0, double fps=2);
    ~DetectionController() {}

public slots:
    void processSequence(QString seq);


signals:
    void newDetection();

private:
    DetectorManager manager;
    double fps;
    double frameHop;
};

#endif // DETECTIONCONTROLLER_H
