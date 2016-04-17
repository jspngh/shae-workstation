#include "signalslot_persistence_test.h"

SignalSlotPersistenceTest::SignalSlotPersistenceTest(QObject *parent) : QObject(parent)
{

}

void SignalSlotPersistenceTest::initTestCase()
{
    m = new Mediator();
    pc = new PersistenceController();
    pc->setMediator(m);

    testSaveSearch();
    qDebug() << "Test";
    testSaveDronePaths();
}

void SignalSlotPersistenceTest::testSaveSearch()
{
    m->addSignal(this, (char *) SIGNAL(startSearch(Search *)), QString("startSearch(Search*)"));
    Search *s = new Search();
    Drone *d= new Drone();
    DroneModule *dm = new DroneModule();
    dm->setDrone(d);
    QList<DroneModule*> droneList;
    droneList.append(dm);
    s->setDroneList(droneList);
    emit startSearch(s);

    m->addSignal(this, SIGNAL(pathCalculated(Search *)), QString("pathCalculated(Search*)"));
    QGeoCoordinate *start = new QGeoCoordinate(51.022671, 3.709903);
    SimplePathAlgorithm *spa = new SimplePathAlgorithm(*start);
    QGeoCoordinate *topLeft = new QGeoCoordinate(51.022882, 3.709684);
    QGeoCoordinate *bottomRight = new QGeoCoordinate(51.022367, 3.710182);
    QGeoRectangle *area = new QGeoRectangle(*topLeft, *bottomRight);
    spa->setWaypointsForDrones(*area, droneList);
    emit pathCalculated(s);

    Search receivedSearch = pc->retrieveSearch(s->getSearchID());
    QVERIFY(s->getSearchID() == receivedSearch.getSearchID());
    QVERIFY(s->getFpsProcessing() == receivedSearch.getFpsProcessing());
    QVERIFY(s->getGimbalAngle() == receivedSearch.getGimbalAngle());
    QVERIFY(s->getHeight() == receivedSearch.getHeight());
    QVERIFY(s->getStartTime() == receivedSearch.getStartTime());
    QVERIFY(s->getDroneList().length() == receivedSearch.getDroneList().length());

    foreach (DroneModule *dm1, droneList)
    {
        //QVERIFY(receivedSearch.getDroneList().contains(dm1));
        foreach (DroneModule *dm2, receivedSearch.getDroneList())
        {
            qDebug() << "dm2" << dm2->getGuid();
            if (dm1->getGuid() == dm2->getGuid())
            {
                Drone *d2 = dm2->getDrone();
                QVERIFY(d->getControllerIp() == d2->getControllerIp());
                QVERIFY(d->getDroneIp() == d2->getDroneIp());
                QVERIFY(d->getDronePort() == d2->getDronePort());
                QVERIFY(d->getGuid() == d2->getGuid());
                QVERIFY(d->getStreamPath() == d2->getStreamPath());
                QVERIFY(d->getStreamPort() == d2->getStreamPort());
                QVERIFY(d->getVisionWidth() == d2->getVisionWidth());
            } else {
                qDebug() << dm1->getGuid();
                qDebug() << dm2->getGuid();
            }
        }
    }
}

void SignalSlotPersistenceTest::testSaveDronePaths()
{
    m->addSignal(this, (char *) SIGNAL(pathCalculated(Search *)), QString("pathCalculated(Search*)"));
    Search *s = new Search();
    Drone *d= new Drone();
    DroneModule *dm = new DroneModule();
    dm->setDrone(d);
    QGeoCoordinate *wp1 = new QGeoCoordinate(12.34, 34.56);
    QGeoCoordinate *wp2 = new QGeoCoordinate(43.21, 65.43);
    QGeoCoordinate *wp3 = new QGeoCoordinate(13.24, 35.46);
    dm->addWaypoint(*wp1);
    dm->addWaypoint(*wp2);
    dm->addWaypoint(*wp3);
    qDebug() << "Done6";
    QList<DroneModule*> droneList;
    qDebug() << "Done5";
    droneList.append(dm);
    qDebug() << "Done4";
    s->setDroneList(droneList);
    qDebug() << "Done3";
    emit pathCalculated(s);

    qDebug() << "Done1";
    QList<QGeoCoordinate> paths = pc->retrieveDronePaths(d->getGuid(), s->getSearchID());

    qDebug() << "Done2";
    foreach (QGeoCoordinate waypoint, *(dm->getWaypoints()))
    {
        QVERIFY(paths.contains(waypoint));
    }

}
