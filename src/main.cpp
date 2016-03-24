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
   QList<Drone*> *droneList; QGeoRectangle area;
   Search* s = new Search();
   s->setHeight(3);
   s->setGimbalAngle(65);
   Mediator* m;
   // "dependencies/drone_stream.mpg"
   QString footage = "dependencies/testfootage.mp4";
   cv::VideoCapture capture = cv::VideoCapture(footage.toStdString());
   DetectionController* d = new DetectionController(m, s, 2, capture);
   d->start();
   d->wait();
}
