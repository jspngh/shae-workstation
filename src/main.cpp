#include <QApplication>
#include <QFile>
#include "controller.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":styles/main.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        a.setStyleSheet(file.readAll());
        file.close();
    }

    MainWindow w;
    w.show();

    Controller *controller = new Controller(&w);
    controller->run();

    return a.exec();
}

