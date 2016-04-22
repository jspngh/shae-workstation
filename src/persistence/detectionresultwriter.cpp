#include "detectionresultwriter.h"
#include "models/detectionresult.h"

#include <QFile>
#include <QList>
#include <QString>
#include <QTextStream>
#include <QXmlStreamWriter>


DetectionResultWriter::DetectionResultWriter()
{

}
void DetectionResultWriter::writeDetectionResultToFileXML(QString fileName, QList<DetectionResult> results)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("DetectionResults");
        for (DetectionResult detectionResult : results) {
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

void DetectionResultWriter::writeDetectionResultToFileTXT(QString fileName, QList<DetectionResult> results)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream( &file );
        stream << "******************************************" << endl;
        stream << "*            DETECTION RESULTS           *" << endl;
        stream << "******************************************" << endl;
        stream << "score             longitude       latitude" << endl;
        stream << "------------------------------------------" << endl;
        for (DetectionResult detectionResult : results) {
             stream << QString::number(detectionResult.getScore())
                       .append("\t\t")
                       .append(QString::number(detectionResult.getLocation().longitude()))
                       .append("\t\t")
                       .append(QString::number(detectionResult.getLocation().latitude()))
                       << endl;
        }
        file.close();
    }
}


