#ifndef VIDEOCONTROLLER_H
#define VIDEOCONTROLLER_H
#include <mutex>
#include <QObject>
#include <QUuid>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

#include <vlc/vlc.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "models/videosequence.h"

class VideoController : public QObject
{
    Q_OBJECT
public:
    VideoController(QObject *parent = 0);
    ~VideoController() {}

public slots:
    void onStartStream(QUuid drone, QString sdpFile);
    void onStopStream(QUuid drone);
signals:
    void streamStarted(VideoSequence seq);
    void streamStopped();
private:
    libvlc_media_player_t *mp;
    libvlc_instance_t *inst;
    libvlc_media_t *m;

};
#endif // VIDEOCONTROLLER_H
