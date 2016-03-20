#include "detectioncontroller_test.h"

using namespace std;

DetectionController_Test::DetectionController_Test(QObject *parent) : QObject(parent)
{

}

void DetectionController_Test::initTestCase()
{
    this->controller = new DetectionController(nullptr);

    QObject::connect(this->controller, &DetectionController::newDetection,
                     this, &DetectionController_Test::onNewDetection);

    this->numDetections = 0;
    this->threadId = QThread::currentThreadId();
}


void DetectionController_Test::testProcessSequence()
{
    std::cout << "Main thread in: " << QThread::currentThreadId() << std::endl;

    this->controller->processSequence(QString("footage/GOPR0016_cropped.mp4"));

    QVERIFY(this->numDetections == 1);
}

void DetectionController_Test::cleanupTestCase()
{
    delete this->controller;
}


// This function is NOT a Unit Test.
// It is used to count the number of times the newDetection signal is emitted in the controller.
void DetectionController_Test::onNewDetection()
{
    ++(this->numDetections);
    std::cout <<  "new detection #" << (this->numDetections) << std::endl;
}


