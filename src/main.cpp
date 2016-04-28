#include <QApplication>
#include <QDebug>
#include "core/controller.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<DetectionResult*>("DetectionResult*");
    qRegisterMetaType<VideoSequence*>("VideoSequence*");
    qRegisterMetaType<Search*>("Search*");
    qRegisterMetaType<DroneStatus*>("DroneStatus*");
    qRegisterMetaType<Drone*>("Drone*");

    MainWindow w;
    w.show();

    Controller controller(&w);
    controller.init();
    return a.exec();
}

