#include "videostreamdetection.h"

VideostreamDetection_Test::VideostreamDetection_Test()
{
}

VideostreamDetection_Test::~VideostreamDetection_Test()
{
}

void VideostreamDetection_Test::initTestCase()
{
    QString program = "python";
    QStringList arguments;
    qDebug() << "opening simulator";
    arguments << "../../../drone/simulator/src/simulator.py";
    simulatorProcess = new QProcess(this);
    qDebug() << "simulator opened";
    simulatorProcess->start(program, arguments);

    QThread::sleep(5);
    MainWindow w;
    controller =  new Controller(&w);
    qDebug() << "initialisation of controller";

    QList<DroneModule *>* list  = new QList<DroneModule *>();
    list->append(new DroneModule(6330, 5502, "127.0.0.1", QString("rtp://127.0.0.1:5000"),  0.0001));
    controller->setDrones(list);
    qDebug() << "added local drone module " << controller->getDrones()->size();
    controller->init();


}


void VideostreamDetection_Test::cleanupTestCase()
{

    QFile droneFile("dependencies/drone_stream.mpg");
    droneFile.remove();
    qDebug() << "closing of simulator";
    simulatorProcess->close();
    delete simulatorProcess;
    delete controller;
    qDebug() << "deleting controller";
}

void VideostreamDetection_Test::VideostreamDetectionTest()
{

    controller->getDrones()->first()->getStream();
    //assume that after 5 seconds, the drone is at the correct waypoint.
    QThread::sleep(5);
    qDebug() << "initialisation of stream";
    controller->initStream(controller->getDrones()->first());
    //allow the detectioncontroller to work for 5 s
    QThread::sleep(5);
    controller->stopStream(controller->getDrones()->first());
    controller->getDetectionController()->wait();


}


