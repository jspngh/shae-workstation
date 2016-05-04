#ifndef VIDEOCONTROLLER_H
#define VIDEOCONTROLLER_H

#include <QObject>
#include <QUuid>
#include <QFile>
#include <QDebug>
#include <QThread>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <mutex>
#include <QTextStream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <unistd.h>
#include <vlc/vlc.h>
#include "core/mediator.h"
#include "models/drone.h"
#include "models/videosequence.h"
#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>

/*!
 * \brief The VideoController class can save the stream of the drone given a configuration file or a network address.
 * The VideoController works on a separte thread and is a component of the DroneModule.
 * The VideoController is started and stopped by the DroneModule.
 * \ingroup Videocontroller
 */
class VideoController : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief VideoController constructor that is used by the DroneModule
     */
    VideoController(QObject *parent = 0);
    //! VideoController destructor
    ~VideoController() {}
    //! method to retrieve the video path
    QString getSequencePath();
    //! method to set the video path
    void setSequencePath(QString sp);
    //! a method to set the mediator in order to connect the signals and slots.
    void setMediator(Mediator *m);

public slots:
    /*!
     * \brief onStartStream() is a slot that listens to a signal to start the stream. The inputfile is used to start the stream.
     * This string can either contain an rtp address (formatted as rtp://XXX.XXX.XXX.XXX) or as an sdp file (formatted as xxx.sdp)
     * As this slot is non-blocking, the VideoSequence is both emitted and returned
     * \param drone is the drone is passed as an argument, in order save the stream with a different name for each drone stream.
     */
    VideoSequence* onStartStream(Drone *drone);
    /*!
     * \brief onStopStream() is a slot that listens to a signal to stop the stream. This slot allows that the stream is correctly closed.
     * \param drone is the drone is passed as an argument, in order save the stream with a different name for each drone stream.
    */
    void onStopStream(Drone *drone);

private:
    QString standardDataFolder();
    QString streamMpgLocation();
    QString streamAviLocation();
    QString streamSdpLocation();

    /**
     * \brief initSdpFile will copy the sololink.sdp file from the qt resources to a writeable and accessable location
     * This only needs to happens once (first the the application needs the file.
     */
    void initSdpFile();
    void removeExistingVideoFiles();

signals:
    /*!
     * \brief streamStarted is a signal that indicates that the stream has been started.
     */
    void streamStarted(QUuid droneId, VideoSequence* seq);

    /*!
     * \brief streamStarted is a signal that indicates that the stream has been stopped.
     */
    void streamStopped();
private:
    libvlc_media_player_t *mp = nullptr;
    libvlc_instance_t *inst = nullptr;
    libvlc_media_t *m = nullptr;
    QString sequence_path;
    Mediator *mediator;

};
#endif // VIDEOCONTROLLER_H
