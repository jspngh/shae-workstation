#include "detectionresultwriter.h"
#include "models/detectionresult.h"

#include <QFile>
#include <QList>
#include <QString>
#include <QXmlStreamWriter>


DetectionResultWriter::DetectionResultWriter()
{

}
void DetectionResultWriter::writeDetectionResultToFile(QString fileName, QList<DetectionResult> results)
{
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly))
    {
        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("DetectionResults");
        for(DetectionResult detectionResult : results)
        {
            xmlWriter.writeStartElement("DetectionResult");
            xmlWriter.writeStartElement("Score");
            xmlWriter.writeCharacters(QString::number(detectionResult.getScore()));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("Latitude");
            xmlWriter.writeCharacters(QString::number(detectionResult.getLocation().latitude()));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("Longitude");
            xmlWriter.writeCharacters(QString::number(detectionResult.getLocation().longitude()));
            xmlWriter.writeEndElement();
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
        file.close();
    }
}

