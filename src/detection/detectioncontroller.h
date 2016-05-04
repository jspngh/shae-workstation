#ifndef DETECTIONCONTROLLER_H
#define DETECTIONCONTROLLER_H

#include <QDebug>
#include <QFileInfo>
#include <QObject>
#include <QString>
#include <QThread>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>
#include <QtCore>
#include <QDir>
#include <QResource>
#include "communication/dronemodule.h"
#include "core/mediator.h"
#include "detection/DetectorManager.h"
#include "models/detectionresult.h"
#include "models/search.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "persistence/persistencecontroller.h"

/*!
 * \brief The DetectionController class is the component that is used by a DroneModule
 * to analyze the drone footage for human detection. The DetectionController works on a separate thread.
 * The DetectionController is started and stopped by the DroneModule.
 * \ingroup Detection
 */
class DetectionController : public QThread
{
    Q_OBJECT

public:
    /*!
     * \brief DetectionController constructor that is used by the DroneModule
     * \param search is a Search object that defines the search for which the DetectionController is used.
     * Contains parameters that are required for the DetectionController.
     * \param dronemodule is the DroneModule object in which the DetectionController is contained.
     * Contains parameters that are required for the DetectionController.
     * \param persistencecontroller is used by the DetectionController to save DetectionResults.
     */
    explicit DetectionController(Search *search, DroneModule *dronemodule, PersistenceController *persistencecontroller, QObject *parent = 0);
    //! DetectionController destructor
    ~DetectionController() {}

    //! a method to set the mediator in order to connect the signals and slots.
    void setMediator(Mediator *mediator);

    /*!
     * \brief streamFinished() can be called when the stream is finished (and no videocontent will thus be provided anymore).
     * The DetectionController component will continue to process the remaining frames, and when all are processed, the DetectionController will automatically close.
     */
    void streamFinished();
    /*!
     * \brief run() starts the DetectionController component
     */
    void run() Q_DECL_OVERRIDE;
    /*!
     * \brief allows to easily retrieve the number of detections that have already occured.
     */
    int getNrDetections();
    //! method to obtain the VideoCapture
    cv::VideoCapture getSequence() const;
    //! method to set the VideoCapture
    void setSequence(const cv::VideoCapture &value);
    //! method to set the video path
    void setPath(const QString &value);

signals:
    /*!
     * \brief the signal that is emitted when a new detection result has been found in the footage.
     */
    void newDetection(QUuid droneId, DetectionResult* result);
    /*!
     * \brief the signal that is emitted when the DetectionController is finished. This requires the function streamFinished() to be
     * called beforehand.
     */
    void detectionFinished();

private:
    DetectorManager* manager;
    cv::VideoCapture sequence;
    Mediator *mediator;
    double fps;
    double frameHop;
    int nrDetections;
    volatile bool streaming;
    Search *search;
    DroneModule *droneModule;
    QUuid droneId;
    QString path;
    PersistenceController *persistenceController;
    /*!
     * \brief allows to parse the configuration file of the DetectionController.
     * This file contains the parameters that are required to calculate the position of a detection, based on the location of the frame, and the position
     * in the frame.
     * \param height is the height of drone during the search
     * \param gimbalAngle is the gimbalAngle of the drone camera.
     */
    void parseConfiguration(QFile& file);

    void parseLut(QTextStream& in, int length, std::vector<vector<double>>& lut);
    /*!
     * \brief analyzes a frame, associated with a given timestamp
     * \param frame is the frame that needs to be analyzed
     * \param time is the timestamp associated with the frame
     */
    void extractDetectionsFromFrame(cv::Mat frame, QDateTime time);

    /*!
     * \brief modelLocation will return the location (path) were the application stores its data.
     * On ubuntu LTS system this path is ~/.local/share/name-app/
     * \return path were the model is stored if it exists
     */
    QString modelLocation();

    /*!
     * \brief initFile will copy the acf model (acf.xml) from resources to the path obtained via the method modelLocation.
     */
    void initAcfModelFile();

    /*!
     * \brief initSearchConfigFile will open the configuration file which resides in the resources and then call parseConfiguration
     */
    void initSearchConfigFile(int height, int gimbalAngle);

    int processHeight;
    int processWidth;
    int resolutionHeight;
    int resolutionWidth;
    std::vector<vector<double>> xLUT;
    std::vector<vector<double>> yLUT;
};

#endif // DETECTIONCONTROLLER_H
