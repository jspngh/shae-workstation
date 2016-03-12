#include "core/simplepathalgorithm_test.h"
#include "core/detectioncontroller_test.h"

#include <QTest>

int main(int argc, char *argv[])
{
    SimplePathAlgorithm_Test test1;
    DetectionController_Test test2;

    QTest::qExec(&test1);
    QTest::qExec(&test2);

    return 0;
}
