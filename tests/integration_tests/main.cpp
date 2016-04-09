#include "core/system_test.h"
#include "core/videostreamdetection_test.h"
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

    //tests.append(new VideostreamDetection_Test());
    tests.append(new System_Test());
    foreach (QObject *test, tests) {
        QTest::qExec(test, a.arguments());
    }
    qDeleteAll(tests.begin(), tests.end());
    db.removeDatabase();
    return 0;
}


