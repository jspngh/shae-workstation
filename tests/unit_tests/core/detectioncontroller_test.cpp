#include "detectioncontroller_test.h"

using namespace std;

DetectionController_Test::DetectionController_Test(QObject *parent) : QObject(parent)
{

}

void DetectionController_Test::initTestCase()
{
    this->controller = new DetectionController();

    QObject::connect(this->controller, &DetectionController::newDetection,
                     this, &DetectionController_Test::onNewDetection);

    this->numDetections = 0;
    this->threadId = QThread::currentThreadId();
}

<<<<<<< HEAD

void DetectionController_Test::testProcessSequence(){
=======
// This function is NOT a Unit Test.
// It is used to count the number of times the newDetection signal is emitted in the controller.
void DetectionController_Test::onNewDetection()
{
    ++(this->numDetections);
    std::cout <<  "new detection #" << (this->numDetections) << std::endl;
}

void DetectionController_Test::testQueue()
{
>>>>>>> fe6385d11e0833c15a4b907450e23216fa34965a
    std::cout << "Main thread in: " << QThread::currentThreadId() << std::endl;

    this->controller->processSequence(QString("footage/GOPR0016_cropped.mp4"));

    QVERIFY(this->numDetections == 1);
}

<<<<<<< HEAD
void DetectionController_Test::cleanupTestCase(){
=======
void DetectionController_Test::cleanupTestCase()
{
    this->controllerThread->quit();
>>>>>>> fe6385d11e0833c15a4b907450e23216fa34965a
    delete this->controller;
}



// This function is NOT a Unit Test.
// It is used to count the number of times the newDetection signal is emitted in the controller.
void DetectionController_Test::onNewDetection(){
    ++(this->numDetections);
    std::cout <<  "new detection #" << (this->numDetections) << std::endl;
}


