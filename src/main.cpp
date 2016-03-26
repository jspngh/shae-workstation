#include <QApplication>
#include "core/controller.h"
#include "mainwindow.h"
#include "pathlogic/geopolygon.h"

int quicktestgeopolygon()
{
    //TODO:There is still some error
    qDebug() << GeoPolygon().toString();
    QList<QGeoCoordinate> list = QList<QGeoCoordinate>();
    list.push_back(QGeoCoordinate(1.0,1.0));
     list.push_back(QGeoCoordinate(2.0,3.0));
    list.push_back(QGeoCoordinate(2.0,2.0));

    list.push_back(QGeoCoordinate(0.0,4.0));
    list.push_back(QGeoCoordinate(-1.5,3.0));
    list.push_back(QGeoCoordinate(-2.0,2.0));
    list.push_back(QGeoCoordinate(-1.0,1.0));

    GeoPolygon polygon = GeoPolygon(list);
    bool b = polygon.isValid();
    qDebug() << polygon.toString();
    return 0;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    Controller controller(&w);
    controller.init();
    quicktestgeopolygon();

    return a.exec();
}


