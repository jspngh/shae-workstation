#ifndef VIDEOCONTROLLER_TEST_H
#define VIDEOCONTROLLER_TEST_H

#include <QObject>
#include <iostream>
#include <QDebug>
#include <QtTest>
#include <string>
#include <QThread>
#include <QUuid>
#include <fstream>



#include "videocontroller/videocontroller.h"

class VideoController_Test : public QObject
{
    Q_OBJECT
public:
    explicit VideoController_Test(QObject *parent = 0);

signals:
    void startStream(Drone *drone);
    void stopStream(Drone *drone);



private Q_SLOTS:
    void testCreateFile();
    void initTestCase();
    void cleanupTestCase();

private:
    void onStreamStarted();
    void onStreamStopped();

    bool started, stopped;
    VideoController vc;
};

#endif // VIDEOCONTROLLER_TEST_H
