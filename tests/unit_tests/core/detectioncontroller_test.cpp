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


void DetectionController_Test::testProcessSequence(){
    this->controller->onProcessSequence(QString("footage/testfootage.mp4"));
    std::this_thread::sleep_for (std::chrono::seconds(1));
    this->controller->onFinish();
    QVERIFY(this->numDetections > 1);
}

void DetectionController_Test::cleanupTestCase()
{
    delete this->controller;
}


// This function is NOT a Unit Test.
// It is used to count the number of times the newDetection signal is emitted in the controller.
void DetectionController_Test::onNewDetection(DetectionResult result){
    ++(this->numDetections);
}


