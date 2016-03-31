#include <QApplication>
#include <QDebug>

#include "core/controller.h"
#include "mainwindow.h"


#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    Controller controller(&w);
    controller.init();

    return a.exec();
}
