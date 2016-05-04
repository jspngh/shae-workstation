#ifndef DRONEHEARTBEAT_INTEGRATIONTEST_H
#define DRONEHEARTBEAT_INTEGRATIONTEST_H
#include <QtTest>
#include "simulatorwrapper.h"
#include "communication/dronemodule.h"
#include "core/controller.h"
#include "ui/mainwindow.h"

class DroneHeartbeat_IntegrationTest : public QObject
{
    Q_OBJECT
public:
    DroneHeartbeat_IntegrationTest();

public slots:
    void onDroneHeartbeatReceived(QString string);

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testReceiveHeartbeat();


private:
    SimulatorWrapper *simulator;
    DroneModule *drone;
    Controller *controller;
    Mediator *m;
    int count;

};

#endif // DRONEHEARTBEAT_INTEGRATIONTEST_H
