#include "core/simplepathalgorithm_test.h"
#include "core/detectioncontroller_test.h"
#include "core/videocontroller_test.h"
#include "core/json_messages_test.h"
#include "core/mediator_test.h"
#include "models/detectionresult.h"

#include <iostream>
#include <QTest>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<DetectionResult>("DetectionResult");
    SimplePathAlgorithm_Test test1;
    DetectionController_Test test2;
    VideoController_Test test3;
    Json_Messages_Test test4;
    Mediator_Test test5;

    QTest::qExec(&test1);
    QTest::qExec(&test2);
    QTest::qExec(&test3);
    QTest::qExec(&test4);
    QTest::qExec(&test5);

    return 0;
}
