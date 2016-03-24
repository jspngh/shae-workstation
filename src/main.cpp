#include <QApplication>
#include "core/controller.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
   //QList<Drone> *droneList; QGeoRectangle area;
   //Search* s = new Search(droneList, area);
   //Mediator* m;
   //DetectionController(m, s, 2, QString("dependencies/testfootage.mp4"))

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Controller controller(&w);
    controller.init();

    return a.exec();
}
