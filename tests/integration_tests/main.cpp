#include "core/droneheartbeat_integrationtest.h"
#include "core/droneconnection_integrationtest.h"
#include "core/dronemodule_integrationtest.h"

#include "core/system_test.h"
#include "core/signalslot_persistence_test.h"
#include "core/databasecreator.h"

#include <QList>
#include <QTest>
#include <QApplication>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QList<QObject *> tests;

    qRegisterMetaType<DetectionResult>("DetectionResult");
    qRegisterMetaType<VideoSequence>("VideoSequence");
    qRegisterMetaType<Search>("Search");
    qRegisterMetaType<DroneStatus>("DroneStatus");
    qRegisterMetaType<Drone>("Drone");

    //create db
    DatabaseCreator db = DatabaseCreator();
    db.removeDatabase();
    db.initDatabase();

    tests.append(new SignalSlotPersistenceTest());
    tests.append(new Dronemodule_IntegrationTest());
    //tests.append(new Dronemodule_IntegrationTest());
    tests.append(new Droneconnection_IntegrationTest());
    tests.append(new DroneHeartbeat_IntegrationTest());

    tests.append(new System_Test());

    foreach (QObject *test, tests) {
        QTest::qExec(test, a.arguments());
    }
    qDeleteAll(tests.begin(), tests.end());

    db.removeDatabase();
    return 0;
}


