#ifndef DETECTIONRESULTWRITER_H
#define DETECTIONRESULTWRITER_H

#include "models/detectionresult.h"
#include <QList>
#include <QString>

class DetectionResultWriter
{
public:
    DetectionResultWriter();

    void writeDetectionResultToFileXML(QString fileName, QList<DetectionResult*>* results);
    void writeDetectionResultToFileTXT(QString fileName, QList<DetectionResult*>* results);
};

#endif // DETECTIONRESULTWRITER_H
