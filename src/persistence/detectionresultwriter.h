#ifndef DETECTIONRESULTWRITER_H
#define DETECTIONRESULTWRITER_H

#include "models/detectionresult.h"
#include <QList>
#include <QString>

class DetectionResultWriter
{
public:
    DetectionResultWriter();

    void writeDetectionResultToFile(QString fileName, QList<DetectionResult*>* results);
};

#endif // DETECTIONRESULTWRITER_H
