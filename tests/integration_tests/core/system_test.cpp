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
    Search *s = new Search();
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
    QTest::qWait(5000000);
}


void System_Test::cleanupTestCase()
{

}

void System_Test::systemTest()
{

}
