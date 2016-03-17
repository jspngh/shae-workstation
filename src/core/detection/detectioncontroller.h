#ifndef DETECTIONCONTROLLER_H
#define DETECTIONCONTROLLER_H

#include <QString>
#include <QDebug>
#include <QObject>
#include <thread>
#include <iostream>

#include "detection/detection/DetectorManager.h"
#include "core/models/detectionresult.h"


class DetectionController : public QObject
{
    Q_OBJECT

public:
    DetectionController(QObject *parent = 0, double fps=2);
    ~DetectionController() {}

public slots:
    void onProcessSequence(QString seq);
    void onFinish();


signals:
    void newDetection(DetectionResult result);

private:
    DetectorManager manager;
    double fps;
    double frameHop;
    volatile bool streaming;
};

#endif // DETECTIONCONTROLLER_H
