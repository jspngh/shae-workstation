#ifndef VIDEOSTREAMDETECTION_H
#define VIDEOSTREAMDETECTION_H



#include <QString>
#include <QProcess>
#include <QtTest/QtTest>
#include <QApplication>
#include "core/controller.h"
#include "ui/mainwindow.h"

class VideostreamDetection_Test : public QObject
{
    Q_OBJECT

private:
    Controller * controller;
    QProcess *simulatorProcess;

public:
    VideostreamDetection_Test();
    ~VideostreamDetection_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void VideostreamDetectionTest();
};

#endif // VIDEOSTREAMDETECTION_H
