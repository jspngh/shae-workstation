#include "core/videostreamdetection.h"
#include "core/droneheartbeat_integrationtest.h"
#include "core/droneconnection_integrationtest.h"
#include "core/dronemodule_integrationtest.h"
#include <QList>
#include <QTest>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QList<QObject *> tests;



 tests.append(new DroneHeartbeat_IntegrationTest());


   tests.append(new Dronemodule_IntegrationTest());


   //TODO: somethig is still wrong when closing this test
 tests.append(new Droneconnection_IntegrationTest());






    //tests.append(new VideostreamDetection_Test());

    foreach (QObject *test, tests) {
        QTest::qExec(test, a.arguments());
    }
    qDeleteAll(tests.begin(), tests.end());



    return 0;
}


