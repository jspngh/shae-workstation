#ifndef DETECTIONCONTROLLER_TEST_H
#define DETECTIONCONTROLLER_TEST_H

#include <QObject>
#include <iostream>
#include <QDebug>
#include <QtTest>
#include <string>
#include <QThread>

#include "core/detectioncontroller.h"

class DetectionController_Test : public QObject
{
    Q_OBJECT
public:
    explicit DetectionController_Test(QObject *parent = 0);

signals:
    void newSequence(QString seq);

private:
    void onNewDetection();

private Q_SLOTS:
    void testProcessSequence();
    void initTestCase();
    void cleanupTestCase();

private:
    DetectionController *controller;
    QThread *controllerThread;

    Qt::HANDLE threadId; // the threadId of the the thread creating this object
    int numDetections = 0; // will count the number of times the onNewDetection slot is emitted
};

#endif // DETECTIONCONTROLLER_TEST_H
