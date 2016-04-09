#include "system_test.h"

System_Test::System_Test()
{
}

System_Test::~System_Test()
{
}

void System_Test::initTestCase()
{

    MainWindow w;
    controller =  new Controller(&w);
    controller->init();

    //setup signals and slots
    qDebug() << "adding ConfigWidget signal/slots";
    controller->getMediator()->addSignal(this, (char *) SIGNAL(startSearch(Search *)), QString("startSearch(Search*)"));

    QList<DroneModule *>* list  = new QList<DroneModule *>();
    list->append(controller->getDrones()->first());
    s = new Search();
    //the following parameters are defined through configwidget
    s->setFpsProcessing(2);
    s->setGimbalAngle(65);
    s->setHeight(3);
    s->setStartTime(QTime::currentTime());
    s->setSearchID(QUuid::createUuid());
    s->setArea(QGeoRectangle(QGeoCoordinate(51.022883, 3.709591), QGeoCoordinate(51.022306, 3.710001)));
    s->setDroneList((*list));

    emit startSearch(s);
    qDebug() << "emit ConfigWidget::startSearch(Search *s)";
    //assume that after 5  seconds, the drone is at the correct waypoint.
    QTest::qWait(1000*10);
    controller->initStream(controller->getDrones()->first());
    QTest::qWait(1000*10);
    //assume that after 10  seconds, the drone is at the final waypoint.
    controller->stopStream(controller->getDrones()->first());
    controller->getDetectionController()->wait();
}


void System_Test::cleanupTestCase()
{
    QFile droneFile("dependencies/drone_stream.mpg");
    droneFile.remove();
    delete controller;
    delete s;
}

void System_Test::systemTest()
{

}
