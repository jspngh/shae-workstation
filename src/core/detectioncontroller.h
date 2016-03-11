#ifndef DETECTIONCONTROLLER_H
#define DETECTIONCONTROLLER_H

#include <QString>

#include "utils/queue.h"

class DetectionController : public QThread
{
    Q_OBJECT
public:
    DetectionController() = default;

public slots:
    void addSequence(QString sequenceName);

signals:
    void newDetection();

protected:
    void run() Q_DECL_OVERRIDE;

private:
    Queue<QString> sequencesQueue; //!< Thread safe queue containing the sequences that needs to be processed by the detector
};

#endif // DETECTIONCONTROLLER_H
