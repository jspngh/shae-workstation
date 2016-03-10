#include <QApplication>
#include <QFile>
#include <QDebug>

#include "mainwindow.h"
#include "communication.h"
#include "drone.h"
#include "simplepathalgorithm.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":styles/main.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        a.setStyleSheet(file.readAll());
        file.close();
    }

    qDebug() << "Starting";
    Communication* comm = new Communication("127.0.0.1", 45896);
    //comm->doRequest("This is a request for the drone");
    Drone drone =Drone();
    drone.waypoints = std::list<QGeoCoordinate>();
    drone.waypoints.push_back(QGeoCoordinate(1.0,1.0));
    drone.waypoints.push_back(QGeoCoordinate(0.0,0.0));
    drone.waypoints.push_back(QGeoCoordinate(-1.0,-1.0));

    drone.sendWaypoints();
    qDebug() << "Request sent";

    MainWindow w;
    w.show();

    return a.exec();
}
