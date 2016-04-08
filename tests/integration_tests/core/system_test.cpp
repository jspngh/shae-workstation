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
    qDebug() << "adding ConfigWidget signal/slots";
    controller->getMediator()->addSignal(this, SIGNAL(startSearch(Search *)), QString("startSearch(Search*)"));
    controller->init();
    //setup signals and slots
    QList<DroneModule *>* list  = new QList<DroneModule *>();
    list->append(new DroneModule(6330, 5502, "127.0.0.1", "127.0.0.1", "127.0.0.1", QString("rtp://127.0.0.1:5000"),  0.0001));
    controller->setDrones(list);

    Search *s = new Search();
    s->setArea(QGeoRectangle(QGeoCoordinate(51.022883, 3.709591), QGeoCoordinate(51.022306, 3.710001)));
    emit startSearch(s);
    qDebug() << "emit ConfigWidget::startSearch(Search *s)";
}


void System_Test::cleanupTestCase()
{

}

void System_Test::systemTest()
{

}
