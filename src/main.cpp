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

    Controller controller = Controller(a);
    controller.run();

    MainWindow w = MainWindow(controller);
    w.show();

    return a.exec();
}

