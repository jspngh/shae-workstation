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
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <unistd.h>
#include <vlc/vlc.h>
#include "models/drone.h"
#include "models/videosequence.h"


class VideoController : public QObject
{
    Q_OBJECT
public:
    //! DetectionController is a class, that retrieves a video stream and saves it to a file
    VideoController(QObject *parent = 0);
    ~VideoController() {}
    QString getSequencePath();
    void setSequencePath(QString sp);

public slots:
    /*!
     * \brief onStartStream() is a slot that listens to a signal to start the stream. The inputfile is used to start the stream.
     * This string can either contain an rtp address (formatted as rtp://XXX.XXX.XXX.XXX) or as an sdp file (formatted as xxx.sdp)
     * As this slot is non-blocking, the VideoSequence is both emitted and returned
     */
    VideoSequence onStartStream(Drone * drone);
    /*!
     * \brief onStopStream() is a slot that listens to a signal to stop the stream. This slot allows that the stream is correctly closed.
     */
    void onStopStream(Drone *drone);

signals:
    /*!
     * \brief streamStarted is a signal that indicates that the stream has been started.
     */
    void streamStarted(VideoSequence seq);
    /*!
     * \brief streamStarted is a signal that indicates that the stream has been stopped.
     */
    void streamStopped();
private:
    libvlc_media_player_t *mp;
    libvlc_instance_t *inst;
    libvlc_media_t *m;
    QString sequence_path;

};
#endif // VIDEOCONTROLLER_H
