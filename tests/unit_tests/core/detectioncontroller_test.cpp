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
    QObject::connect(this, &DetectionController_Test::startDetection,
                     this->controller, &DetectionController::onProcessSequence);
    QObject::connect(this, &DetectionController_Test::stopDetection,
                     this->controller, &DetectionController::onFinish);

    this->numDetections = 0;
}


void DetectionController_Test::testProcessSequence(){
    QThread detectionThread;
    this->controller->moveToThread(&detectionThread);
    emit startDetection(QString("dependencies/testfootage.mp4"));
    std::this_thread::sleep_for (std::chrono::seconds(1));
    emit stopDetection();
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


