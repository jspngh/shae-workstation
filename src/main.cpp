#include <QApplication>
#include <QFile>
#include <QDebug>

#include "mainwindow.h"
#include "communication.h"
#include "drone.h"
#include "simplepathalgorithm.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":styles/main.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        a.setStyleSheet(file.readAll());
        file.close();
    }

    qDebug() << "Starting";
    //Communication* comm = new Communication("10.1.1.10", 6330);
    Communication* comm = new Communication("127.0.0.1", 45896);
    //comm->doRequest("This is a request for the drone");
    // Drone drone =Drone(0.000005);
    Drone* drone = new Drone(comm, 0.00001);
    //drone.waypoints = std::list<QGeoCoordinate>();
    //drone.waypoints.push_back(QGeoCoordinate(1.0,1.0));
    //drone.waypoints.push_back(QGeoCoordinate(0.0,0.0));
    //drone.waypoints.push_back(QGeoCoordinate(-1.0,-1.0));
    std::list<Drone*>* l= new std::list<Drone*>();
    l->push_back(drone);
    SimplePathAlgorithm algo = SimplePathAlgorithm(QGeoCoordinate(51.022668,3.709749));
    algo.setWaypointsForDrones(QGeoRectangle(QGeoCoordinate(51.022668,3.709749),QGeoCoordinate(51.022401,3.709868)),l);
    //drone->sendWaypoints();
    drone->startFlight();
    qDebug() << "Request sent";
    usleep(1000000);
    drone->requestHeartbeat();
    usleep(1000000);
    qDebug() << "Request sent";

    drone->requestStatus(Location);
    qDebug() << "Request sent";
    usleep(1000000);
    drone->setSetting(Speed,20);
    qDebug() << "Request sent";
    usleep(1000000);

    MainWindow w;
    w.show();

    return a.exec();
}
