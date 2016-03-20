#include "detectioncontroller_test.h"

using namespace std;

DetectionController_Test::DetectionController_Test(QObject *parent) : QObject(parent)
{
}

void DetectionController_Test::initTestCase()
{
    this->controller = new DetectionController(nullptr,2,"dependencies/testfootage.mp4");
    QObject::connect(this->controller, &DetectionController::newDetection,
                     this, &DetectionController_Test::onNewDetection);
    this->numDetections = 0;
}


void DetectionController_Test::testProcessSequence()
{
    this->controller->start();
    QThread::sleep(1);
    this->controller->streamFinished();
    QThread::sleep(10);
    int count = this->controller->getNrDetections();
    this->controller->quit();
    delete this->controller;
    QVERIFY(count > 1);
}

void DetectionController_Test::cleanupTestCase()
{

}

// This function is NOT a Unit Test.
// It is used to count the number of times the newDetection signal is emitted in the controller.
void DetectionController_Test::onNewDetection(DetectionResult result){
    ++(this->numDetections);
}
