#include <QApplication>
#include <QFile>
#include <QDebug>

#include "mainwindow.h"
#include "communication.h"

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
    comm->doRequest("Can yet fuel melt steal beams?");
    qDebug() << "Request sent";

    MainWindow w;
    w.show();

    return a.exec();
}
