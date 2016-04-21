#include "system_test.h"

System_Test::System_Test()
{
}

System_Test::~System_Test()
{
}

void System_Test::initTestCase()
{

    simulator = new SimulatorWrapper();
    simulator->startSimulator();


    MainWindow w;
    controller =  new Controller(&w);
    controller->init();

    //setup signals and slots
    qDebug() << "adding ConfigWidget signal/slots";
    controller->getMediator()->addSignal(this, SIGNAL(startSearch(Search *)), QString("startSearch(Search*)"));

    QList<DroneModule *> *list  = new QList<DroneModule *>();

    // wait until a drone is connected to the controller
    // the controller needs to wait until the drone sends a hello message, indicating that it is ready
    while (controller->numDronesConnected() < 1) {
        qDebug() << "wait until a drone is connected to the controller";
        QTest::qWait(1000 * 5);
    }

    // select the first drone that has connected to the controller
    DroneModule *drone = (*(controller->getDrones()))[0];
    drone->getDrone()->setStreamPath(QString("dependencies/video_stream.mp4"));
    list->append(drone);

    s = new Search();
    //the following parameters are defined through the configwidget
    s->setFpsProcessing(1);
    s->setGimbalAngle(65);
    s->setHeight(3);
    s->setStartTime(QTime::currentTime());
    s->setSearchID(QUuid::createUuid());
    s->setArea(QGeoRectangle(QGeoCoordinate(51.022883, 3.709591), QGeoCoordinate(51.022683, 3.709591)));
    s->setDroneList((*list));

    emit startSearch(s);
    QTest::qWait(1000 * 10);
    QTest::qWait(1000 * 60 * 4);
}


void System_Test::cleanupTestCase()
{
    QFile droneFile("dependencies/drone_stream.mpg");
    droneFile.remove();

    qDebug() << "closing of simulator";
    simulator->stopSimulator();
    QTest::qWait(500);
    delete simulator;
    QTest::qWait(5000);
    delete controller;
    delete s;
}

void System_Test::systemTest()
{

}
