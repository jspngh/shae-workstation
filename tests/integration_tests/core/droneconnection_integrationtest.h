#ifndef DRONECONNECTION_INTEGRATIONTEST_H
#define DRONECONNECTION_INTEGRATIONTEST_H
#include "simulatorwrapper.h"
#include "communication/dronemodule.h"
#include "core/controller.h"
#include "ui/mainwindow.h"
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
    Controller *controller;
    DroneModule *drone;
    Mediator *m;
    int count;

private slots:
    void onDroneResponse(QString string);

};

#endif // DRONECONNECTION_INTEGRATIONTEST_H
