#ifndef DETECTIONCONTROLLER_TEST_H
#define DETECTIONCONTROLLER_TEST_H

#include <QObject>
#include <iostream>
#include <QDebug>
#include <QtTest>
#include <string>
#include <QThread>
#include <QWaitCondition>
#include <QProcess>
#include "detection/detectioncontroller.h"

class DetectionController_Test : public QObject
{
    Q_OBJECT
public:
    DetectionController_Test(QObject *parent = 0);

private:
    void onNewDetection(DetectionResult result);

private Q_SLOTS:
    void testProcessSequence();
    void testIncorrectParseConfiguration();
    void initTestCase();
    void cleanupTestCase();

private:
    QProcess *simulatorProcess;

    DetectionController *controller;
    int numDetections = 0; // will count the number of times the onNewDetection slot is emitted
};

#endif // DETECTIONCONTROLLER_TEST_H
