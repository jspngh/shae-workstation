#include "system_test.h"

System_Test::System_Test()
{
}

System_Test::~System_Test()
{
}

void System_Test::initTestCase()
{

    QString program = "python2";
    QStringList arguments;
    qDebug() << "opening simulator";
    arguments << "../../../drone/simulator/src/simulator.py";
    simulatorProcess = new QProcess(this);
    qDebug() << "simulator opened";
    simulatorProcess->start(program, arguments);
    QTest::qWait(1000*30);


    MainWindow w;
    controller =  new Controller(&w);
    controller->init();

    //setup signals and slots
    qDebug() << "adding ConfigWidget signal/slots";
    controller->getMediator()->addSignal(this, SIGNAL(startSearch(Search *)), QString("startSearch(Search*)"));

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
    //assume that after 10  seconds, the drone is at the correct waypoint and the system is correctly started
    QTest::qWait(1000*10);
    controller->initStream(controller->getDrones()->first());
    QTest::qWait(1000*20);
    //assume that after 10  seconds, the drone is at the final waypoint.
    controller->stopStream(controller->getDrones()->first());
    QTest::qWait(1000*60*2);
    //after the stream has stopped, no statusses need to be saved anymore
    controller->getDrones()->first()->getDetectionController()->wait();
}


void System_Test::cleanupTestCase()
{
    QFile droneFile("dependencies/drone_stream.mpg");
    droneFile.remove();

    qDebug() << "closing of simulator";
    simulatorProcess->terminate();
    simulatorProcess->waitForFinished();
    simulatorProcess->close();
    delete simulatorProcess;
    delete controller;
    delete s;
}

void System_Test::systemTest()
{

}
