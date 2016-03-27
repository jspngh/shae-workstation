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

#include <QList>
#include <QTest>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Persistence *testPersistence = new Persistence();
    QSqlDatabase* testDataBase = testPersistence->getDatabase();

    QList<QObject*> tests;
    tests.append(new SimplePathAlgorithm_Test());
    tests.append(new Json_Messages_Test());
    tests.append(new DetectionController_Test());
    tests.append(new Mediator_Test());
    tests.append(new SearchDAO_Test(testDataBase));
    tests.append(new DetectionResultDAO_Test(testDataBase));
    tests.append(new DroneDAO_Test(testDataBase));
    tests.append(new DroneSearchDAO_Test(testDataBase));
    tests.append(new DroneStatusDAO_Test(testDataBase));
    tests.append(new VideoSequenceDAO_Test(testDataBase));

    foreach(QObject* test, tests) {
        QTest::qExec(test, a.arguments());
    }

    delete testPersistence;
    delete testDataBase;
    qDeleteAll(tests.begin(), tests.end());

    return 0;
}




