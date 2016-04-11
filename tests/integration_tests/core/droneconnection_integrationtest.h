#ifndef DRONECONNECTION_INTEGRATIONTEST_H
#define DRONECONNECTION_INTEGRATIONTEST_H
#include "simulatorwrapper.h"
#include <QtTest>

class Droneconnection_IntegrationTest : public QObject
{
    Q_OBJECT
public:
    Droneconnection_IntegrationTest();


private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testDroneConnection();

};

#endif // DRONECONNECTION_INTEGRATIONTEST_H
