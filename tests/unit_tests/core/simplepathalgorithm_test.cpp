#include <QString>
#include <QtWidgets/QtWidgets>
#include <QtTest/QtTest>
#include "communication/communication.h"
#include "pathlogic/pathalgorithm.h"
#include "pathlogic/simplepathalgorithm.h"
#include "models/drone.h"
#include "simplepathalgorithm_test.h"

SimplePathAlgorithm_Test::SimplePathAlgorithm_Test()
{
}

SimplePathAlgorithm_Test::~SimplePathAlgorithm_Test()
{
}

void SimplePathAlgorithm_Test::initTestCase()
{
}

void SimplePathAlgorithm_Test::cleanupTestCase()
{
}

void SimplePathAlgorithm_Test::testSimplePathAlgorithm()
{
    //initiate area, start point and algorithm.
    QGeoRectangle area = QGeoRectangle(QGeoCoordinate(10.0, 0.0), QGeoCoordinate(0.0, 10.0));
    QGeoCoordinate start = QGeoCoordinate(2.0, 2.0);
    SimplePathAlgorithm algorithm = SimplePathAlgorithm(start);
    QList<QGeoCoordinate> calculatedList = algorithm.calculateWaypoints(area, 2.0);

    //Create testlist
    QList<QGeoCoordinate> testList = QList<QGeoCoordinate>();
    testList.push_back(QGeoCoordinate(0.0, 0.0));
    testList.push_back(QGeoCoordinate(10.0, 0.0));
    testList.push_back(QGeoCoordinate(10.0, 2.0));
    testList.push_back(QGeoCoordinate(0.0, 2.0));
    testList.push_back(QGeoCoordinate(0.0, 4.0));
    testList.push_back(QGeoCoordinate(10.0, 4.0));
    testList.push_back(QGeoCoordinate(10.0, 6.0));
    testList.push_back(QGeoCoordinate(0.0, 6.0));
    testList.push_back(QGeoCoordinate(0.0, 8.0));
    testList.push_back(QGeoCoordinate(10.0, 8.0));
    testList.push_back(QGeoCoordinate(10.0, 10.0));
    testList.push_back(QGeoCoordinate(0.0, 10.0));

    //Do the checks
    double epsilon = 0.00000001;
    int listSize = 12;
    for (int i = 0; i < listSize; i++) {
        QGeoCoordinate calculated = calculatedList.front();
        QGeoCoordinate test = testList.front();

        calculatedList.pop_front();
        testList.pop_front();

        //compare
        QVERIFY(fabs(calculated.latitude()- test.latitude())<epsilon);
        QVERIFY(fabs(calculated.longitude()- test.longitude())<epsilon);
    }

}

void SimplePathAlgorithm_Test::testSimplePathAlgorithm2()
{

    //initiate area, start point and algorithm.
    QGeoRectangle area = QGeoRectangle(QGeoCoordinate(1.0, -1.0), QGeoCoordinate(-1.0, 1.0));
    QGeoCoordinate start = QGeoCoordinate(20.0, 20.0);
    SimplePathAlgorithm algorithm = SimplePathAlgorithm(start);
    QList< QGeoCoordinate> calculatedList = algorithm.calculateWaypoints(area, 0.3);

    //Create testlist
    QList< QGeoCoordinate> testList = QList< QGeoCoordinate>();
    testList.push_back(QGeoCoordinate(1.0, 1.0));
    testList.push_back(QGeoCoordinate(-1.0, 1.0));
    testList.push_back(QGeoCoordinate(-1.0, 0.7));
    testList.push_back(QGeoCoordinate(1.0, 0.7));
    testList.push_back(QGeoCoordinate(1.0, 0.4));
    testList.push_back(QGeoCoordinate(-1.0, 0.4));
    testList.push_back(QGeoCoordinate(-1.0, 0.1));
    testList.push_back(QGeoCoordinate(1.0, 0.1));
    testList.push_back(QGeoCoordinate(1.0, -0.2));
    testList.push_back(QGeoCoordinate(-1.0, -0.2));
    testList.push_back(QGeoCoordinate(-1.0, -0.5));
    testList.push_back(QGeoCoordinate(1.0, -0.5));
    testList.push_back(QGeoCoordinate(1.0, -0.8));
    testList.push_back(QGeoCoordinate(-1.0, -0.8));
    testList.push_back(QGeoCoordinate(-1.0, -1.1));
    testList.push_back(QGeoCoordinate(1.0, -1.1));


    //Do the checks
    double epsilon = 0.000001;
    int listSize = testList.size();
    for (int i = 0; i < listSize; i++) {
        QGeoCoordinate calculated = calculatedList.front();
        QGeoCoordinate test = testList.front();

        calculatedList.pop_front();
        testList.pop_front();

        //Compare

        QVERIFY(fabs(calculated.latitude()- test.latitude())<epsilon);
        QVERIFY(fabs(calculated.longitude()- test.longitude())<epsilon);

    }
}

void SimplePathAlgorithm_Test::testSimplePathAlgorithm3()
{

    //initiate area, start point and algorithm.
    QGeoRectangle area = QGeoRectangle(QGeoCoordinate(1.0, -1.0), QGeoCoordinate(-1.0, 1.0));
    QGeoCoordinate start =  QGeoCoordinate(-20.0, 20.0);
    SimplePathAlgorithm algorithm = SimplePathAlgorithm(start);

    QList< QGeoCoordinate> calculatedList = algorithm.calculateWaypoints(area, 0.6);

    //Create testlist
    QList< QGeoCoordinate> testList = QList< QGeoCoordinate>();
    testList.push_back(QGeoCoordinate(-1.0, 1.0));
    testList.push_back(QGeoCoordinate(1.0, 1.0));
    testList.push_back(QGeoCoordinate(1.0, 0.4));
    testList.push_back(QGeoCoordinate(-1.0, 0.4));
    testList.push_back(QGeoCoordinate(-1.0, -0.2));
    testList.push_back(QGeoCoordinate(1.0, -0.2));
    testList.push_back(QGeoCoordinate(1.0, -0.8));
    testList.push_back(QGeoCoordinate(-1.0, -0.8));
    testList.push_back(QGeoCoordinate(-1.0, -1.4));
    testList.push_back(QGeoCoordinate(1.0, -1.4));


    //Do the checks
    double epsilon = 0.000001;
    int listSize = testList.size();
    for (int i = 0; i < listSize; i++) {
        QGeoCoordinate calculated = calculatedList.front();
        QGeoCoordinate test = testList.front();

        calculatedList.pop_front();
        testList.pop_front();

        //Compare
        QVERIFY(fabs(calculated.latitude()- test.latitude())<epsilon);
        QVERIFY(fabs(calculated.longitude()- test.longitude())<epsilon);

    }
}

void SimplePathAlgorithm_Test::testSimplePathAlgorithmWithMultipleDrones()
{

    QList<Drone*>* drones = new QList<Drone*>();
    Drone* droneA = new Drone();
    droneA->setVisionWidth(2.0);
    Drone* droneB = new Drone();
    droneB->setVisionWidth(2.0);

    drones->push_back(droneA);
    drones->push_back(droneB);

    QGeoRectangle area = QGeoRectangle(QGeoCoordinate(8.0,0.0),QGeoCoordinate(0.0,8.0));
    SimplePathAlgorithm algorithm = SimplePathAlgorithm(QGeoCoordinate(1.0,1.0));
    algorithm.setWaypointsForDrones(area, drones);
    QList<QGeoCoordinate> testList1 = QList<QGeoCoordinate>();
    QList<QGeoCoordinate> testList2 = QList<QGeoCoordinate>();


    testList1.push_back(QGeoCoordinate(0.0, 0.0));
    testList1.push_back(QGeoCoordinate(8.0, 0.0));
    testList1.push_back(QGeoCoordinate(8.0, 2.0));
    testList1.push_back(QGeoCoordinate(0.0, 2.0));
    testList1.push_back(QGeoCoordinate(0.0, 4.0));
    testList1.push_back(QGeoCoordinate(8.0, 4.0));

    testList2.push_back(QGeoCoordinate(0.0, 4.0));
    testList2.push_back(QGeoCoordinate(8.0, 4.0));
    testList2.push_back(QGeoCoordinate(8.0, 6.0));
    testList2.push_back(QGeoCoordinate(0.0, 6.0));
    testList2.push_back(QGeoCoordinate(0.0, 8.0));
    testList2.push_back(QGeoCoordinate(8.0, 8.0));

    //check if drones->front().waypoints == testList1
    double epsilon = 0.000001;
    int listSize = testList1.size();
    Drone* frontDrone = drones->front();
    QList<QGeoCoordinate> frontDroneList = frontDrone->getWaypoints();

    for(int i=0; i<listSize; i++){
        QGeoCoordinate calculated = frontDroneList.front();
        QGeoCoordinate test = testList1.front();

        frontDroneList.pop_front();
        testList1.pop_front();

        //Compare
        QVERIFY(fabs(calculated.latitude()- test.latitude())<epsilon);
        QVERIFY(fabs(calculated.longitude()- test.longitude())<epsilon);
    }

    //check if drones->back().waypoints == testList2
    listSize = testList2.size();
    Drone* backDrone = drones->back();
    QList<QGeoCoordinate> backDroneList = backDrone->getWaypoints();

    for(int i=0; i<listSize; i++){
        QGeoCoordinate calculated = backDroneList.front();
        QGeoCoordinate test = testList2.front();

        backDroneList.pop_front();
        testList2.pop_front();

        //Compare
        QVERIFY(fabs(calculated.latitude() - test.latitude())<epsilon);
        QVERIFY(fabs(calculated.longitude() - test.longitude())<epsilon);

    }

    delete droneA;
    delete droneB;
    delete drones;
}

void SimplePathAlgorithm_Test::testSimplePathAlgorithmWithMultipleDrones2()
{
    QList<Drone*>* drones = new QList<Drone*>();
    Drone* droneA = new Drone();
    droneA->setVisionWidth(1.5);
    Drone* droneB = new Drone();
    droneB->setVisionWidth(2.0);
    drones->push_back(droneA);
    drones->push_back(droneB);

    QGeoRectangle area = QGeoRectangle(QGeoCoordinate(8.0,0.0),QGeoCoordinate(0.0,8.0));
    SimplePathAlgorithm algorithm = SimplePathAlgorithm(QGeoCoordinate(5.0,5.0));
    algorithm.setWaypointsForDrones(area, drones);
    QList<QGeoCoordinate> testList1 = QList<QGeoCoordinate>();
    QList<QGeoCoordinate> testList2 = QList<QGeoCoordinate>();

    testList1.push_back(QGeoCoordinate(8.0,4.0));
    testList1.push_back(QGeoCoordinate(0.0,4.0));
    testList1.push_back(QGeoCoordinate(0.0,2.5));
    testList1.push_back(QGeoCoordinate(8.0,2.5));
    testList1.push_back(QGeoCoordinate(8.0,1.0));
    testList1.push_back(QGeoCoordinate(0.0,1.0));
    testList1.push_back(QGeoCoordinate(0.0,-0.5));
    testList1.push_back(QGeoCoordinate(8.0,-0.5));

    testList2.push_back(QGeoCoordinate(8.0,4.0));
    testList2.push_back(QGeoCoordinate(0.0,4.0));
    testList2.push_back(QGeoCoordinate(0.0,6.0));
    testList2.push_back(QGeoCoordinate(8.0,6.0));
    testList2.push_back(QGeoCoordinate(8.0,8.0));
    testList2.push_back(QGeoCoordinate(0.0,8.0));

    //check if drones->front().waypoints == testList1
    double epsilon = 0.000001;
    int listSize = testList1.size();
    Drone* frontDrone = drones->front();
    QList<QGeoCoordinate> frontDroneList = frontDrone->getWaypoints();

    for(int i=0; i<listSize; i++) {
        QGeoCoordinate calculated = frontDroneList.front();
        QGeoCoordinate test = testList1.front();

        frontDroneList.pop_front();
        testList1.pop_front();

        //Compare
        QVERIFY(fabs(calculated.latitude()- test.latitude())<epsilon);
        QVERIFY(fabs(calculated.longitude()- test.longitude())<epsilon);
    }

    //check if drones->back().waypoints == testList2
    listSize = testList2.size();
    Drone* backDrone = drones->back();
    QList<QGeoCoordinate> backDroneList = backDrone->getWaypoints();

    for(int i=0; i<listSize; i++) {
        QGeoCoordinate calculated = backDroneList.front();
        QGeoCoordinate test = testList2.front();

        backDroneList.pop_front();
        testList2.pop_front();

        //Compare
        QVERIFY(fabs(calculated.latitude() - test.latitude())<epsilon);
        QVERIFY(fabs(calculated.longitude() - test.longitude())<epsilon);
    }

    delete droneA;
    delete droneB;
    delete drones;
}
