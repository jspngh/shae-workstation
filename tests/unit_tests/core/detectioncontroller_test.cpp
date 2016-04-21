#include "detectioncontroller_test.h"

using namespace std;

DetectionController_Test::DetectionController_Test(QObject *parent) : QObject(parent)
{
}

void DetectionController_Test::initTestCase()
{
    DroneModule *dm = new DroneModule(6330, 5502, "127.0.0.1", "127.0.0.1", "127.0.0.1", QString("rtp://127.0.0.1:5000"),  0.0001);
    QList<DroneModule *> droneList;
    droneList.append(dm);
    Search *s = new Search();
    s->setHeight(3);
    s->setGimbalAngle(65);
    s->setFpsProcessing(2);
    s->setDroneList(droneList);
    Mediator *m = new Mediator();
    PersistenceController *pc = new PersistenceController();
    pc->setMediator(m);
    // "dependencies/drone_stream.mpg"
    QString footage = "dependencies/testfootage.mp4";
    VideoController *videoController = new VideoController();
    videoController->setSequencePath(footage);
    cv::VideoCapture capture = cv::VideoCapture(footage.toStdString());
    dm->setVideoController(videoController);
    this->controller = new DetectionController(s, dm, pc);
    this->controller->setSequence(capture);
    this->controller->setPath(footage);

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

    QVERIFY(count >= 0);
}

void DetectionController_Test::cleanupTestCase()
{

    delete this->controller;

}
