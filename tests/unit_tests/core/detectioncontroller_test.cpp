#include "detectioncontroller_test.h"

DetectionController_Test::DetectionController_Test(QObject *parent) : QObject(parent)
{

}

void DetectionController_Test::test1(){
    DetectorManager manager;
    QVERIFY(1 == 0);
}

// QTEST_MAIN(DetectionController_Test)
