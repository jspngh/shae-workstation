#ifndef DETECTIONCONTROLLER_H
#define DETECTIONCONTROLLER_H

#include <QDebug>
#include <QFileInfo>
#include <QObject>
#include <QString>
#include <QThread>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "communication/dronemodule.h"
#include "core/mediator.h"
#include "detection/DetectorManager.h"
#include "models/detectionresult.h"
#include "models/search.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "persistence/persistencecontroller.h"

class DetectionController : public QThread
{
    Q_OBJECT

public:
    //! DetectionController is a class, implemented as a thread, that parses a video sequence and emits the detection results as a signal
    explicit DetectionController(Search *search, DroneModule *dm, PersistenceController *pc, QObject *parent = 0);
    ~DetectionController() {}

    void setMediator(Mediator *mediator);

    /*!
     * \brief streamFinished() can be called when the stream is finished (and no videocontent will thus be provided anymore).
     * The DetectionController component will continue to process the remaining frames, and when all are processed, will stop the thread.
     */
    void streamFinished();
    /*!
     * \brief run() starts the DetectionController component
     * This function has no coordinates, but needs to be configured with the correct parameters.
     * \param fps contains the fps at which the stream will be parsed
     * \param sequence is an OpenCV VideoCapture. The VideoCapture is the videocapture of the stream. It is required
     * to pass a VideoCapture, as the OpenCV Library does not allow to open videocaptures from threads different from the main thread.
     * \return signals containing detection results
     */
    void run() Q_DECL_OVERRIDE;
    /*!
     * \brief getNrDetections() allows to easily retrieve the number of detections that have already been retrieved.
     */
    int getNrDetections();

    cv::VideoCapture getSequence() const;
    void setSequence(const cv::VideoCapture &value);

signals:
    /*!
     * \brief the signal that is emitted when a new detection result has been found in the footage.
     */
    void newDetection(QUuid droneId, DetectionResult result);
    /*!
     * \brief the signal that is emitted when the detectionController is finished. This requires the function streamFinished() to be
     * called beforehand.
     */
    void detectionFinished();


private:
    DetectorManager manager;
    cv::VideoCapture sequence;
    Mediator *mediator;
    double fps;
    double frameHop;
    int nrDetections;
    volatile bool streaming;
    Search *search;
    DroneModule * droneModule;
    QUuid droneId;
    QString path;
    PersistenceController *persistenceController;
    /*!
     * \brief a private method that allows to parse the configuration file of the detectioncontroller
     * this file contains the parameters that are required to calculate the position of a detection, based on the location of the frame, and the position
     * in the frame
     */
    void parseConfiguration(int height, int gimbalAngle);
    /*!
     * \brief xLUT and yLUT are lookuptables that are required for position calculation
     */
    void extractDetectionsFromFrame(cv::Mat frame, QDateTime time);

    std::vector<vector<double>> xLUT;
    std::vector<vector<double>> yLUT;
};

#endif // DETECTIONCONTROLLER_H
