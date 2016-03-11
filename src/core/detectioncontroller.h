#ifndef DETECTIONCONTROLLER_H
#define DETECTIONCONTROLLER_H

#include <QString>
#include <QDebug>

#include "utils/queue.h"
#include "../../libs/detection/detection/DetectorManager.h"

class DetectionController : public QThread
{
    Q_OBJECT

public:
    DetectionController() = default;

    QString smallTest(){
        QDebug << QString("Hello");
        return QString("Hello");
    }

public slots:
    void addSequence(QString sequenceName);

signals:
    void newDetection();

protected:
    void run() Q_DECL_OVERRIDE;

private:
    Queue<QString> sequencesQueue; //!< Thread safe queue containing the sequences that needs to be processed by the detector
    DetectorManager manager;
    WindowSelection wndSelector;
    Detector detector;
};

#endif // DETECTIONCONTROLLER_H
