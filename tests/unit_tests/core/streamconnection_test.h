#ifndef STREAMCONNECTION_TEST_H
#define STREAMCONNECTION_TEST_H
#include <QtTest>
#include <QObject>
#include "communication/streamconnection.h"

class StreamConnection_Test: public QObject
{
    Q_OBJECT

public:
    StreamConnection_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanUpTestCase();
    void testConstructor();
    void testDestructor();
    void testStopConnection();
    //void testOnStreamRequest(); is an integration test
};

#endif // STREAMCONNECTION_TEST_H
