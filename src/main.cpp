#include <QApplication>
#include <QDebug>
#include "core/controller.h"
#include "mainwindow.h"
#include <QFile>
#include <QString>

QString modelLocation();

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

QString modelLocation()
{
    QString folder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QString name = "acf.xml";

    //create folder if not available
    QDir(QDir::root()).mkpath(folder);

    if (!folder.endsWith(QDir::separator()))
        folder.append(QDir::separator());


    return folder.append(name);
}


