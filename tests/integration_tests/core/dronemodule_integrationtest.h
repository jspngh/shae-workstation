#ifndef DRONEMODULE_INTEGRATIONTEST_H
#define DRONEMODULE_INTEGRATIONTEST_H
#include <QtTest>
#include "simulatorwrapper.h"
#include "communication/dronemodule.h"
#include "ui/mainwindow.h"
#include "core/controller.h"


class Dronemodule_IntegrationTest: public QObject
{
    Q_OBJECT

public:
    Dronemodule_IntegrationTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testNavigationMessages();
    void testStatusMessages();
    void testSettingsMessages();

private:
    SimulatorWrapper *sim;
    Controller *controller;
    DroneModule *drone;
    Mediator *m;
    int count;

private slots:
    void onDroneResponse(QString string);
};

#endif // DRONEMODULE_INTEGRATIONTEST_H
