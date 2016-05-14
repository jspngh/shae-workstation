#include "polygonpathalgorithm_test.h"

PolygonPathAlgorithm_Test::PolygonPathAlgorithm_Test()
{

}

PolygonPathAlgorithm_Test::~PolygonPathAlgorithm_Test()
{

}

void PolygonPathAlgorithm_Test::initTestCase()
{


}

void PolygonPathAlgorithm_Test::cleanupTestCase()
{

}

void PolygonPathAlgorithm_Test::testCalculateWaypoints()
{
    auto algorithm = PolygonPathAlgorithm(QGeoCoordinate(0.0, 0.0));
    QList<QGeoCoordinate> coordinates;
    coordinates.push_back(QGeoCoordinate(1.0, 1.0));
    coordinates.push_back(QGeoCoordinate(2.0, 2.0));
    coordinates.push_back(QGeoCoordinate(1.0, 3.0));

    GeoPolygon area = GeoPolygon(coordinates);
    auto calculatedList = algorithm.calculateWaypoints(area, 0.5);

    //would be great to check if every spot is covered (andnot too much outside of the area is covered)
    //instead of just the calculated waypoints, but thats probably too hard

    auto testList = new QList<QGeoCoordinate>();
    testList->push_back(QGeoCoordinate(1.0, 1.0));
    testList->push_back(QGeoCoordinate(1.5, 1.5));
    testList->push_back(QGeoCoordinate(1.0, 1.5));
    testList->push_back(QGeoCoordinate(1.0, 2.0));
    testList->push_back(QGeoCoordinate(2.0, 2.0));
    testList->push_back(QGeoCoordinate(1.5, 2.5));
    testList->push_back(QGeoCoordinate(1.0, 2.5));
    testList->push_back(QGeoCoordinate(1.0, 3.0));

    int n = testList->size();
    QVERIFY(n == calculatedList->size());
    for (int i = 0; i < n; i++) {
        QVERIFY((*testList)[i] == (*calculatedList)[i]);
    }

    delete calculatedList;
    delete testList;
}

void PolygonPathAlgorithm_Test::testSetWaypointsForDrones()
{
    auto algorithm = PolygonPathAlgorithm(QGeoCoordinate(0.0, 0.0));
    QList<QGeoCoordinate> coordinates;
    coordinates.push_back(QGeoCoordinate(1.0, 1.0));
    coordinates.push_back(QGeoCoordinate(2.0, 2.0));
    coordinates.push_back(QGeoCoordinate(1.0, 3.0));

    coordinates.push_back(QGeoCoordinate(0.0, 2.0));

    GeoPolygon area = GeoPolygon(coordinates);
    QList<DroneModule *> drones;
    DroneModule *drone1 = new DroneModule();
    drone1->setVisionWidth(0.5);
    DroneModule *drone2 = new DroneModule();
    drone2->setVisionWidth(0.5);

    drones.push_back(drone1);
    drones.push_back(drone2);
    algorithm.setWaypointsForDrones(area, drones);

    QList<QGeoCoordinate> testList1 = QList<QGeoCoordinate>();
    QList<QGeoCoordinate> testList2 = QList<QGeoCoordinate>();

    testList1.push_back(QGeoCoordinate(1.0, 1.0));
    testList1.push_back(QGeoCoordinate(1.5, 1.5));
    testList1.push_back(QGeoCoordinate(0.5, 1.5));
    testList1.push_back(QGeoCoordinate(2.0, 2.0));

    testList2.push_back(QGeoCoordinate(0.0, 2.0));
    testList2.push_back(QGeoCoordinate(0.0, 2.5));
    testList2.push_back(QGeoCoordinate(0.5, 2.5));
    testList2.push_back(QGeoCoordinate(1.0, 3.0));


    //check if drones.front().waypoints == testList1
    double epsilon = 0.000001;
    int listSize = testList1.size();
    DroneModule *frontDrone = drones.front();
    QList<QGeoCoordinate> *frontDroneList = frontDrone->getWaypoints();


    //QVERIFY(listSize == frontDroneList->size());
    for (int i = 0; i < listSize; i++) {
        QGeoCoordinate calculated = (*frontDroneList)[i];
        QGeoCoordinate test = testList1[i];

        //Compare
        QVERIFY(fabs(calculated.longitude() - test.longitude()) < epsilon);
        QVERIFY(fabs(calculated.latitude() - test.latitude()) < epsilon);

    }

    //check if drones.back().waypoints == testList2
    listSize = testList2.size();
    DroneModule *backDrone = drones.back();
    QList<QGeoCoordinate> *backDroneList = backDrone->getWaypoints();

    for (int i = 0; i < listSize; i++) {
        QGeoCoordinate calculated = (*backDroneList)[i];
        QGeoCoordinate test = testList2[i];

        qDebug() << calculated;
        //Compare
        QVERIFY(fabs(calculated.latitude() - test.latitude()) < epsilon);
        QVERIFY(fabs(calculated.longitude() - test.longitude()) < epsilon);
    }

    delete drone1;
    delete drone2;
}

void PolygonPathAlgorithm_Test::testGetNeighbouringEdges()
{
    QGeoCoordinate from = QGeoCoordinate(0.5, 0.5);
    QList<QGeoCoordinate> list;
    list.push_back(QGeoCoordinate(0.0, 0.0));
    list.push_back(QGeoCoordinate(1.0, 1.0));
    auto pair = PolygonPathAlgorithm::getNeighbouringEdges(from, list);

    QVERIFY(pair.first == QGeoCoordinate(0.0, 0.0));
    QVERIFY(pair.second == QGeoCoordinate(1.0, 1.0));
}

