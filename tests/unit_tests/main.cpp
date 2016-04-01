#include "core/simplepathalgorithm_test.h"
#include "core/detectioncontroller_test.h"
#include "core/searchdao_test.h"
#include "core/detectionresultdao_test.h"
#include "core/dronedao_test.h"
#include "core/dronesearchdao_test.h"
#include "core/dronestatusdao_test.h"
#include "core/videosequencedao_test.h"
#include "core/json_messages_test.h"
#include "core/mediator_test.h"
#include "core/databasecreator.h"
#include "core/videocontroller_test.h"
#include "core/json_messages_test.h"
#include "core/mediator_test.h"
#include "models/detectionresult.h"
#include <QList>
#include <QTest>
#include <QApplication>

int main(int argc, char *argv[])
{
    qRegisterMetaType<DetectionResult>("DetectionResult");
    QApplication a(argc, argv);

    DatabaseCreator db = DatabaseCreator();
    db.initDatabase();

    QList<QObject*> tests;
    tests.append(new SimplePathAlgorithm_Test());
    tests.append(new Json_Messages_Test());
    tests.append(new DetectionController_Test());
    //tests.append(new VideoController_Test());
    tests.append(new Mediator_Test());
    tests.append(new SearchDAO_Test());
    tests.append(new DetectionResultDAO_Test());
    tests.append(new DroneDAO_Test());
    tests.append(new DroneSearchDAO_Test());
    tests.append(new DroneStatusDAO_Test());
    tests.append(new VideoSequenceDAO_Test());

    foreach(QObject* test, tests) {
        QTest::qExec(test, a.arguments());
    }

    qDeleteAll(tests.begin(), tests.end());
    db.removeDatabase();

    return 0;
}




