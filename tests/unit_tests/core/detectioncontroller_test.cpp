#include "detectioncontroller_test.h"

using namespace std;

DetectionController_Test::DetectionController_Test(QObject *parent) : QObject(parent)
{
}

void DetectionController_Test::initTestCase()
{
    Search *s = new Search();
    s->setHeight(3);
    s->setGimbalAngle(65);
    Mediator *m;
    // "dependencies/drone_stream.mpg"
    QString footage = "dependencies/testfootage.mp4";
    cv::VideoCapture capture = cv::VideoCapture(footage.toStdString());
    this->controller = new DetectionController(m, s, 2, capture);
    QObject::connect(this->controller, &DetectionController::newDetection,
                     this, &DetectionController_Test::onNewDetection);
    this->numDetections = 0;
}


void DetectionController_Test::testProcessSequence()
{
    //start the detectioncontroller on a separate thread
    this->controller->start();
    QThread::sleep(1);
    //indicate that the stream has stopped (the controller should finish analyzing all the frames)
    this->controller->streamFinished();
    //check if the controller has signalled detections in the past 10s
    QThread::sleep(10);
    int count = this->controller->getNrDetections();
    QVERIFY(count > 1);
}

void DetectionController_Test::cleanupTestCase()
{
    this->controller->wait();
    delete this->controller;

}

// This function is NOT a Unit Test.
// It is used to count the number of times the newDetection signal is emitted in the controller.
void DetectionController_Test::onNewDetection(DetectionResult result)
{
    ++(this->numDetections);
}
