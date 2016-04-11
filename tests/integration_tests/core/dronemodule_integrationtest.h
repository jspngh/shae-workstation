#ifndef DRONEMODULE_INTEGRATIONTEST_H
#define DRONEMODULE_INTEGRATIONTEST_H
#include <QtTest>
#include "simulatorwrapper.h"


class Dronemodule_IntegrationTest: public QObject
{
    Q_OBJECT

public:
    Dronemodule_IntegrationTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
};

#endif // DRONEMODULE_INTEGRATIONTEST_H
