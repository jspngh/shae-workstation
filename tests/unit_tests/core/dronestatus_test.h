#ifndef DRONESTATUS_TEST_H
#define DRONESTATUS_TEST_H

#include <QObject>
#include <QString>
#include <QUuid>
#include <QtWidgets/QtWidgets>
#include <QtTest/QtTest>
#include "models/dronestatus.h"

class DroneStatus_Test : public QObject
{
    Q_OBJECT
public:
    DroneStatus_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testDefaultConstructor();
    void testConstructor();
    void testLongConstructor();
    void testCopyConstructor();
    void testFromJsonStringAllSet();
    void testFromJsonStringNoneSet();
    void testParseExceptionNotJson();
    void testParseExceptionNotStatus();

};

#endif // DRONESTATUS_TEST_H
