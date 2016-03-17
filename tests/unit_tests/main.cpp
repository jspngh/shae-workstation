#include "core/simplepathalgorithm_test.h"
#include "core/detectioncontroller_test.h"
#include "core/videocontroller_test.h"

#include <QTest>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SimplePathAlgorithm_Test test1;
    DetectionController_Test test2;
    VideoController_Test test3;

    QTest::qExec(&test1);
    QTest::qExec(&test2);
    QTest::qExec(&test3);

    return a.exec();
}
