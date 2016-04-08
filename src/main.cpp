#include <QApplication>
#include <QDebug>

#include "core/controller.h"
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    Controller controller(&w);
    controller.init();

    return a.exec();
}

