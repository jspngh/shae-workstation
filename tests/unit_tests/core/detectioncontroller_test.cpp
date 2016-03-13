#include "detectioncontroller_test.h"

using namespace std;

DetectionController_Test::DetectionController_Test(QObject *parent) : QObject(parent)
{

}

void DetectionController_Test::testQueue(){
    DetectionController c;
    c.addSequence(QString("sequence#1"));
    c.addSequence(QString("sequence#2"));
    c.addSequence(QString("sequence#3"));
    c.addSequence(QString("sequence#4"));

    QThread thr;
    c.moveToThread(&thr);
    c.startProcessing();
}


