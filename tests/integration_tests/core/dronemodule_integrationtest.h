#ifndef DRONEMODULE_INTEGRATIONTEST_H
#define DRONEMODULE_INTEGRATIONTEST_H
#include <QtTest>
#include "simulatorwrapper.h"
#include "communication/dronemodule.h"


class Dronemodule_IntegrationTest: public QObject
{
    Q_OBJECT

public:
    Dronemodule_IntegrationTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testNavigationMessages();
    void testStatusMessages();
    void testSettingsMessages();

private:
    SimulatorWrapper* sim;
    DroneModule* drone;
    Mediator* m;
    QThread th;
    int count;

private slots:
    void onDroneResponse(QString string);
};

#endif // DRONEMODULE_INTEGRATIONTEST_H
