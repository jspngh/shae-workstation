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
    //! DetectionController is a class, implemented as a thread, that parses a video sequence and emits the detection results as a signal
    explicit DetectionController(Mediator *mediator, Search *search, double fps, cv::VideoCapture sequence, QObject *parent = 0);
    ~DetectionController() {}
    // Setter

    void setController(Controller *value);

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

signals:
    /*!
     * \brief the signal that is emitted when a new detection result has been found in the footage.
     */
    void newDetection(DetectionResult result);
    /*!
     * \brief the signal that is emitted when the detectionController is finished. This requires the function streamFinished() to be
     * called beforehand.
     */
    void detectionFinished();




private:
    DetectorManager manager;
    cv::VideoCapture sequence;
    double fps;
    double frameHop;
    int nrDetections;
    volatile bool streaming;
    Search *search;
    /*!
     * \brief a private method that allows to parse the configuration file of the detectioncontroller
     * this file contains the parameters that are required to calculate the position of a detection, based on the location of the frame, and the position
     * in the frame
     */
    void parseConfiguration();
    /*!
     * \brief xLUT and yLUT are lookuptables that are required for position calculation
     */
    std::vector<vector<double>> xLUT;
    std::vector<vector<double>> yLUT;
};

#endif // DETECTIONCONTROLLER_H
