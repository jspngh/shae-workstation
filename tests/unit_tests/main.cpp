#include "core/simplepathalgorithm_test.h"
#include "core/detectioncontroller_test.h"
<<<<<<< HEAD
#include "core/searchdao_test.h"
=======
#include "core/json_messages_test.h"
>>>>>>> develop

#include <QTest>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SimplePathAlgorithm_Test test1;
<<<<<<< HEAD
    DetectionController_Test test2;
    SearchDAO_Test test3;
=======
    Json_Messages_Test test2;
    DetectionController_Test test3;

>>>>>>> develop

    QTest::qExec(&test1);
    QTest::qExec(&test2);
    QTest::qExec(&test3);

    return a.exec();
}
