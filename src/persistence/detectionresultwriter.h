#ifndef DETECTIONRESULTWRITER_H
#define DETECTIONRESULTWRITER_H

#include "models/detectionresult.h"
#include <QList>
#include <QString>
/*!
 * \brief The DetectionResultWriter class
 * \ingroup Persistence
 */
class DetectionResultWriter
{
public:
    /**
     * \brief The basic constructor for a DetectionResultWriter.
     */
    DetectionResultWriter();

    /**
     * \brief writeDetectionResultToXML needs as input fileName and results.
     * Results are the detection results of the current search.
     * FileName is the path/filename where the detection results need to be stored.
     * Selecting this method will result in a XML type of file.
     */
    void writeDetectionResultToFileXML(QString fileName, QList<DetectionResult *> *results);
    /**
     * \brief writeDetectionResultToXML needs as input fileName and results.
     * Results are the detection results of the current search.
     * FileName is the path/filename where the detection results need to be stored.
     * Selecting this method will result in a TXT type of file.
     */
    void writeDetectionResultToFileTXT(QString fileName, QList<DetectionResult *> *results);
};

#endif // DETECTIONRESULTWRITER_H
