#include <QtTest/QtTest>
#include <QString>
#include "core/detectioncontroller.h"
class Detection_Test : public QObject
{
    Q_OBJECT

public:
    Detection_Test();

private slots:
    void testDetectionControllerInit();
};

void Detection_Test::testDetectionControllerInit(){
    DetectionController detectionController();
    // detectionController.smallTest();
    // detectionController.addSequence();
}

