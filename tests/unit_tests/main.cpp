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

#include <QTest>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SimplePathAlgorithm_Test test1;
    Json_Messages_Test test2;
    DetectionController_Test test3;
    //DAO tests
    SearchDAO_Test test4;
    DetectionResultDAO_Test test5;
    DroneDAO_Test test6;
    DroneSearchDAO_Test test7;
    DroneStatusDAO_Test test8;
    VideoSequenceDAO_Test test9;
    //mediator tests
    Mediator_Test test10;

    QTest::qExec(&test1);
    QTest::qExec(&test2);
    QTest::qExec(&test3);
    QTest::qExec(&test4);
    QTest::qExec(&test5);
    QTest::qExec(&test6);
    QTest::qExec(&test7);
    QTest::qExec(&test8);
    QTest::qExec(&test9);
    QTest::qExec(&test10);

    // a.exec();

    return 0;
}
