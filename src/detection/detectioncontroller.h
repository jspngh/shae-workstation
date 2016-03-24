#ifndef DETECTIONCONTROLLER_H
#define DETECTIONCONTROLLER_H

#include <QString>
#include <QDebug>
#include <QObject>
#include <thread>
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <fstream>
#include "detection/DetectorManager.h"
#include "models/detectionresult.h"
#include "models/search.h"
#include "core/mediator.h"
#include <QDebug>
#include <QFileInfo>

class DetectionController : public QThread{
    Q_OBJECT

public:
    explicit DetectionController(Mediator *mediator, Search *search, double fps, cv::VideoCapture sequence, QObject *parent = 0);
    ~DetectionController() {}
    void streamFinished();
    void run() Q_DECL_OVERRIDE;
    int getNrDetections();

signals:
    void newDetection(DetectionResult result);
    void detectionFinished();



private:
    DetectorManager manager;
    cv::VideoCapture sequence;
    double fps;
    double frameHop;
    int nrDetections;
    volatile bool streaming;
    Search *search;
    void parseConfiguration();
    std::vector<vector<double>> xLUT;
    std::vector<vector<double>> yLUT;
};

#endif // DETECTIONCONTROLLER_H
