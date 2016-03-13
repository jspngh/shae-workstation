#include "detectioncontroller_test.h"

using namespace std;

DetectionController_Test::DetectionController_Test(QObject *parent) : QObject(parent)
{

}

void DetectionController_Test::test1(){
    DetectionController c;
    string detectorType = c.manager.getDetectorType();
    QVERIFY(detectorType == "windows");
}


