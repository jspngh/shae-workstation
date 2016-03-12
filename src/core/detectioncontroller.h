#ifndef DETECTIONCONTROLLER_H
#define DETECTIONCONTROLLER_H

#include <QString>
#include <QDebug>

#include "utils/queue.h"
#include "detection/detection/DetectorManager.h"

class DetectionController : public QObject
{
    Q_OBJECT

public:
    DetectionController(QObject *parent=0);
    ~DetectionController(){
        delete this->wndSelector;
        delete this->detector;
    }

    QString smallTest(){
        qDebug() << "Hello";
        return QString("Hello");
    }

public slots:
    void addSequence(QString sequenceName);

signals:
    void newDetection();

protected:
    // void run() Q_DECL_OVERRIDE;

private:
    // Queue<QString> sequencesQueue; //!< Thread safe queue containing the sequences that needs to be processed by the detector
    DetectorManager manager;
    WindowSelection* wndSelector;
    Detector* detector;
};

#endif // DETECTIONCONTROLLER_H
