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


class VideoController : public QObject
{
    Q_OBJECT
public:
    //! DetectionController is a class, that retrieves a video stream and saves it to a file
    VideoController(QObject *parent = 0);
    ~VideoController() {}
    QString getSequencePath();
    void setSequencePath(QString sp);
    void setMediator(Mediator *m);

public slots:
    /*!
     * \brief onStartStream() is a slot that listens to a signal to start the stream. The inputfile is used to start the stream.
     * This string can either contain an rtp address (formatted as rtp://XXX.XXX.XXX.XXX) or as an sdp file (formatted as xxx.sdp)
     * As this slot is non-blocking, the VideoSequence is both emitted and returned
     */
    VideoSequence* onStartStream(Drone *drone);
    /*!
     * \brief onStopStream() is a slot that listens to a signal to stop the stream. This slot allows that the stream is correctly closed.
     */
    void onStopStream(Drone *drone);

private:
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
