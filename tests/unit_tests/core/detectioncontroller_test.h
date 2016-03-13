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

private Q_SLOTS:
    void testQueue();
};

#endif // DETECTIONCONTROLLER_TEST_H
