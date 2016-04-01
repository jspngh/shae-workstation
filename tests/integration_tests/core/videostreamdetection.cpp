#include "videostreamdetection.h"
#include <QApplication>
#include "core/controller.h"
#include "ui/mainwindow.h"

VideostreamDetection_Test::VideostreamDetection_Test()
{
}

VideostreamDetection_Test::~VideostreamDetection_Test()
{
}

void VideostreamDetection_Test::initTestCase()
{

    int argc = 0;
    char *argv[] = {};
    QApplication a(argc, argv);
    MainWindow w;
    Controller controller(&w);
    controller.init();
    this->KillAppAfterTimeout(20);
    a.exec();
}


void VideostreamDetection_Test::cleanupTestCase()
{
}

void VideostreamDetection_Test::VideostreamDetectionTest()
{
}


bool VideostreamDetection_Test::KillAppAfterTimeout(int secs)
{
    QScopedPointer<QTimer> timer(new QTimer);
    timer->setSingleShot(true);
    bool ok = timer->connect(timer.data(), SIGNAL(timeout()), qApp, SLOT(quit()), Qt::QueuedConnection);
    timer->start(secs * 1000); // N seconds timeout
    timer.take()->setParent(qApp);
    return ok;
}


