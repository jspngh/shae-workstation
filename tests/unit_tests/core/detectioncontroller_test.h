#ifndef DETECTIONCONTROLLER_TEST_H
#define DETECTIONCONTROLLER_TEST_H

#include <QObject>
#include <QtTest/QtTest>

#include "detection/DetectorManager.h"

class DetectionController_Test : public QObject
{
    Q_OBJECT
public:
    explicit DetectionController_Test(QObject *parent = 0);

private Q_SLOTS:
    void test1();
};

#endif // DETECTIONCONTROLLER_TEST_H
