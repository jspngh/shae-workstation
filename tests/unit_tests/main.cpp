#include "core/simplepathalgorithm_test.h"
#include "core/detectioncontroller_test.h"
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
    Mediator_Test test4;

    QTest::qExec(&test1);
    QTest::qExec(&test2);
    QTest::qExec(&test3);
    QTest::qExec(&test4);

    // a.exec();

    return 0;
}
