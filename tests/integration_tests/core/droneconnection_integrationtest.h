#ifndef DRONECONNECTION_INTEGRATIONTEST_H
#define DRONECONNECTION_INTEGRATIONTEST_H
#include "simulatorwrapper.h"
#include "communication/dronemodule.h"
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

private:
    SimulatorWrapper *sim;
    DroneModule *drone;
    Mediator *m;
    QThread th;
    int count;

private slots:
    void onDroneResponse(QString string);

};

#endif // DRONECONNECTION_INTEGRATIONTEST_H
