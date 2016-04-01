#include "pathalgorithm_test.h"
#include "pathlogic/simplepathalgorithm.h"
#include <QApplication>
#include <QDebug>
#include "core/controller.h"
#include "ui/mainwindow.h"


Pathalgorithm_Test::Pathalgorithm_Test()
{

}

Pathalgorithm_Test::~Pathalgorithm_Test()
{

}

void Pathalgorithm_Test::initTestCase()
{

}

void Pathalgorithm_Test::cleanupTestCase()
{

}

void Pathalgorithm_Test::testConstructor1()
{
    SimplePathAlgorithm algo = SimplePathAlgorithm();
    QVERIFY(algo.start == QGeoCoordinate(0.0,0.0));
}

void Pathalgorithm_Test::testConstructor2()
{
    SimplePathAlgorithm algo = SimplePathAlgorithm(QGeoCoordinate(1.0,1.0));
    QVERIFY(algo.start == QGeoCoordinate(1.0,1.0));
}

void Pathalgorithm_Test::testSetController()
{
    SimplePathAlgorithm algo = SimplePathAlgorithm();
    MainWindow w;
    Controller* controller = new Controller(&w);
    algo.setController(controller);


}

void Pathalgorithm_Test::testGoDirectionWest()
{
    SimplePathAlgorithm algo = SimplePathAlgorithm();
    QGeoCoordinate to = PathAlgorithm::goDirection(QGeoCoordinate(0.0,0.0),WEST, 1.0 );
    QVERIFY(to == QGeoCoordinate(0.0,-1.0));

}

void Pathalgorithm_Test::testGoDirectionEast()
{
    SimplePathAlgorithm algo = SimplePathAlgorithm();
    QGeoCoordinate to = PathAlgorithm::goDirection(QGeoCoordinate(0.0,0.0),EAST, 1.0 );
    QVERIFY(to == QGeoCoordinate(0.0,1.0));
}

void Pathalgorithm_Test::testGoDirectionBetween()
{
    SimplePathAlgorithm algo = SimplePathAlgorithm();
    QGeoCoordinate to = PathAlgorithm::goDirectionBetween(QGeoCoordinate(0.0,0.0),QGeoCoordinate(2.0,2.0),QGeoCoordinate(3.0,3.0),1.0, EAST);
    QVERIFY(to == QGeoCoordinate(1.0,1.0));

}
