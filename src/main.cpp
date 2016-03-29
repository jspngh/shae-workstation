#include <QApplication>
#include "core/controller.h"
#include "mainwindow.h"
#include "pathlogic/geopolygon.h"
#include "pathlogic/polygonpathalgorithm.h"

int quicktestgeopolygon()
{
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
    qDebug() << b;
    return 0;
}

int quicktestPolygonPath()
{
    PolygonPathAlgorithm algo = PolygonPathAlgorithm(QGeoCoordinate(-1.0,-1.0));
    GeoPolygon area = GeoPolygon();
    qDebug() << area.toString();
    auto list = algo.calculateWaypoints(area , 0.2);
    for( const QGeoCoordinate& coor : (*list) ){
        qDebug() << coor.latitude() << coor.longitude();
    }
    return 0;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    Controller controller(&w);
    controller.init();
    quicktestPolygonPath();

    return a.exec();
}


