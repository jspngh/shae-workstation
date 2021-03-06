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
#include <QNetworkInterface>

#include "videocontroller/videocontroller.h"
#include "communication/streamconnection.h"



class VideoController_Test : public QObject
{
    Q_OBJECT
public:
    explicit VideoController_Test(QObject *parent = 0);

signals:
    void startStream(Drone *drone);
    void stopStream(Drone *drone);
    void streamRequest();


private Q_SLOTS:
    void testCreateFile();
    void initTestCase();
    void cleanupTestCase();

private:
    void onStreamStarted();
    void onStreamStopped();
    QProcess *simulatorProcess;
    StreamConnection *streamConnection;
    QThread *streamThread;
    bool started, stopped;
    VideoController vc;
};

#endif // VIDEOCONTROLLER_TEST_H
