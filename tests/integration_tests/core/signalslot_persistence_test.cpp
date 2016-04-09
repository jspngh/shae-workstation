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

    Search receivedSearch = pc->retrieveSearch(s->getSearchID());

    QVERIFY(s->getSearchID() == receivedSearch.getSearchID());
    QVERIFY(s->getFpsProcessing() == receivedSearch.getFpsProcessing());
    QVERIFY(s->getGimbalAngle() == receivedSearch.getGimbalAngle());
    QVERIFY(s->getHeight() == receivedSearch.getHeight());
    QVERIFY(s->getStartTime() == receivedSearch.getStartTime());
    QVERIFY(s->getDroneList().length() == receivedSearch.getDroneList().length());

    foreach (DroneModule *dm1, droneList)
    {
        QVERIFY(receivedSearch.getDroneList().contains(dm1));

        int index = receivedSearch.getDroneList().indexOf(dm1);
        Drone *d1 = receivedSearch.getDroneList().at(index)->getDrone();
        QVERIFY(d->getControllerIp() == d1->getControllerIp());
        QVERIFY(d->getDroneIp() == d1->getDroneIp());
        QVERIFY(d->getDronePort() == d1->getDronePort());
        QVERIFY(d->getGuid() == d1->getGuid());
        QVERIFY(d->getStreamPath() == d1->getStreamPath());
        QVERIFY(d->getStreamPort() == d1->getStreamPort());
        QVERIFY(d->getVisionWidth() == d1->getVisionWidth());
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
    QList<DroneModule*> droneList;
    droneList.append(dm);
    s->setDroneList(droneList);
    emit pathCalculated(s);

    QList<QGeoCoordinate> paths = pc->retrieveDronePaths(d->getGuid(), s->getSearchID());

    foreach (QGeoCoordinate waypoint, *(dm->getWaypoints()))
    {
        QVERIFY(paths.contains(waypoint));
    }

}
