#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QUuid>
#include <unistd.h>
#include "core/controller.h"
#include "mainwindow.h"
#include "models/drone.h"
#include "pathlogic/simplepathalgorithm.h"

void testDrone();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // testDrone();

    MainWindow w;
    w.show();

    Controller controller(&w);
    controller.init();
    controller.setWorkstationIP("127.0.0.1");
    controller.setWorkstationHeartbeatPort(6332);

    qDebug() << "here3";
    return a.exec();
}

// This is test code and should not be in main()
void testDrone()
{
    /* qDebug() << "Starting"; */

    /* Drone drone =Drone(0.000005); */
    /* QUuid droneId = QUuid::createUuid(); */
    /* Drone *drone = new Drone(droneId, 6331, "127.0.0.1", 0.0001); */
    /* drone.waypoints = QList<QGeoCoordinate>(); */
    /* drone.waypoints.push_back(QGeoCoordinate(1.0,1.0)); */
    /* drone.waypoints.push_back(QGeoCoordinate(0.0,0.0)); */
    /* drone.waypoints.push_back(QGeoCoordinate(-1.0,-1.0)); */
    /* QList<Drone *> *l = new QList<Drone *>(); */
    /* l->push_back(drone); */
    /* SimplePathAlgorithm algo = SimplePathAlgorithm(QGeoCoordinate(51.022668, 3.709749)); */
    /* algo.setWaypointsForDrones(QGeoRectangle(QGeoCoordinate(51.022668, 3.709749), QGeoCoordinate(51.022401, 3.709868)), l); */

    /* drone->sendWaypoints(); */
    /* usleep(10000); */
    /* drone->startFlight(); */
    /* qDebug() << "Request sent"; */
    /* usleep(10000); */

    /* drone->requestHeartbeat(); */
    /* usleep(10000); */
    /* qDebug() << "Request sent"; */

    /* drone->requestStatus(Location); */
    /* qDebug() << "Request sent"; */
    /* usleep(10000); */
    /* drone->setSetting(Speed_To_Set, 20); */
    /* qDebug() << "Request sent"; */
    /* usleep(10000); */

    /* delete drone; */
    /* delete l; */
}

