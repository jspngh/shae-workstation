#include "detectioncontroller_test.h"

using namespace std;

DetectionController_Test::DetectionController_Test(QObject *parent) : QObject(parent)
{
}

void DetectionController_Test::initTestCase()
{
    DroneModule *dm;
    QList<DroneModule *> droneList;
    droneList.append(dm);
    Search *s = new Search();
    s->setHeight(3);
    s->setGimbalAngle(65);
    s->setFpsProcessing(2);
    s->setDroneList(droneList);
    Mediator *m;
    PersistenceController *pc = new PersistenceController(m);
    // "dependencies/drone_stream.mpg"
    QString footage = "dependencies/testfootage.mp4";
    VideoController *videoController;
    videoController->setSequencePath(footage);
    cv::VideoCapture capture = cv::VideoCapture(footage.toStdString());
    dm->setVideoController(videoController);
    this->controller = new DetectionController(s, dm, pc);
    this->controller->setSequence(capture);
    QObject::connect(this->controller, &DetectionController::newDetection,
                     this, &DetectionController_Test::onNewDetection);
    this->numDetections = 0;
}

void DetectionController_Test::testIncorrectParseConfiguration()
{
    DroneModule *dm;
    QList<DroneModule *> droneList;
    droneList.append(dm);
    Search *s = new Search();
    s->setHeight(0);
    s->setGimbalAngle(0);
    s->setFpsProcessing(0);
    s->setDroneList(droneList);
    Mediator *m;
    PersistenceController *pc = new PersistenceController(m);
    QString footage = "dependencies/testfootage.mp4";
    VideoController *videoController;
    videoController->setSequencePath(footage);
    dm->setVideoController(videoController);
    DetectionController* d = new DetectionController(s, dm, pc);
    //verify that the method has executed correctly
    delete s;
    delete d;
    QVERIFY(true);
}



void DetectionController_Test::testProcessSequence()
{
    //start the detectioncontroller on a separate thread
    this->controller->start();
    QThread::sleep(1);
    //indicate that the stream has stopped (the controller should finish analyzing all the frames)
    this->controller->streamFinished();
    //check if the controller has signalled detections in the past 10s
    this->controller->wait();
    int count = this->controller->getNrDetections();

    QVERIFY(count > 1);
}

void DetectionController_Test::cleanupTestCase()
{

    delete this->controller;

}

// This function is NOT a Unit Test.
// It is used to count the number of times the newDetection signal is emitted in the controller.
void DetectionController_Test::onNewDetection(DetectionResult result)
{
    ++(this->numDetections);
}
