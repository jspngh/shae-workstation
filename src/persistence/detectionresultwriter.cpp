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

void DetectionResultWriter::writeDetectionResultToFileXML(QString fileName, QList<DetectionResult*>* results)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("DetectionFile");
        xmlWriter.writeStartElement("Timestamp");
        xmlWriter.writeCharacters(QDateTime::currentDateTime().toString());
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("DetectionResults");
        for (DetectionResult *detectionResult : *results) {
            xmlWriter.writeStartElement("DetectionResult");
            xmlWriter.writeStartElement("Score");
            xmlWriter.writeCharacters(QString::number(detectionResult->getScore()));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("Latitude");
            xmlWriter.writeCharacters(QString("%1").arg(detectionResult->getLocation().latitude(),0,'f',15));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("Longitude");
            xmlWriter.writeCharacters(QString("%1").arg(detectionResult->getLocation().longitude(),0,'f',15));
            xmlWriter.writeEndElement();
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
        file.close();
    }
}

void DetectionResultWriter::writeDetectionResultToFileTXT(QString fileName, QList<DetectionResult*>* results)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream( &file );
        stream << "Timestamp: " << QDateTime::currentDateTime().toString() << endl;
        stream << "******************************************" << endl;
        stream << "*            DETECTION RESULTS           *" << endl;
        stream << "******************************************" << endl;
        stream << "score             longitude       latitude" << endl;
        stream << "------------------------------------------" << endl;
        for (DetectionResult* detectionResult : *results) {
            QString detectionString = QString("%1\t\t%2\t\t%3");
            QString js = detectionString
                         .arg(detectionResult->getScore())
                         .arg(detectionResult->getLocation().latitude(),0,'f',15).arg(detectionResult->getLocation().longitude(),0,'f',15);
             stream << js << endl;
        }
        file.close();
    }
}


