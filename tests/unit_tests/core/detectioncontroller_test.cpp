#include "detectioncontroller_test.h"

DetectionController_Test::DetectionController_Test(QObject *parent) : QObject(parent)
{

}

void DetectionController_Test::test1(){
    DetectionController c;
    int g = c.smallTest();
    std::cout << g << std::endl;
    QVERIFY(g == 5);
}


