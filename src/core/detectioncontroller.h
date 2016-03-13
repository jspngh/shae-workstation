#ifndef DETECTIONCONTROLLER_H
#define DETECTIONCONTROLLER_H

#include <QString>
#include <QDebug>
#include <QObject>

#include "utils/queue.h"
#include "detection/detection/DetectorManager.h"

class DetectionController : public QObject
{
    Q_OBJECT

public:
    DetectionController(QObject *parent=0);
    ~DetectionController(){

    }

    int smallTest(){
        return 5;
    }

public slots:
    void addSequence(QString sequenceName);

signals:
    void newDetection();

protected:
    // void run() Q_DECL_OVERRIDE;

public:
    Queue<QString> sequencesQueue; //!< Thread safe queue containing the sequences that needs to be processed by the detector
    DetectorManager manager;
};

#endif // DETECTIONCONTROLLER_H
