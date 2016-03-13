#include "detectioncontroller_test.h"

DetectionController_Test::DetectionController_Test(QObject *parent) : QObject(parent)
{

}

void DetectionController_Test::test1(){
    DetectionController c;
    std::cout << c.manager.getDetectorType() << std::endl;
    // int g = c.smallTest();
    // std::cout << (g) << std::endl;
    QVERIFY(10 == 10);
}


