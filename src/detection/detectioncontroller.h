#ifndef DETECTIONCONTROLLER_H
#define DETECTIONCONTROLLER_H

#include <QString>
#include <QDebug>
#include <QObject>
#include <thread>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "detection/DetectorManager.h"
#include "models/detectionresult.h"
#include "core/mediator.h"

class DetectionController : public QThread{
    Q_OBJECT

public:
    explicit DetectionController(Mediator *mediator, double fps=2, QString sequence = "dependencies/drone_stream.mpg", QObject *parent = 0);
    ~DetectionController() {}
    void streamFinished();
    void run() Q_DECL_OVERRIDE;
    int getNrDetections();


signals:
    void newDetection(DetectionResult result);
    void detectionFinished();



private:
    DetectorManager manager;
    QString sequence;
    double fps;
    double frameHop;
    int nrDetections;
    volatile bool streaming;
};

#endif // DETECTIONCONTROLLER_H
