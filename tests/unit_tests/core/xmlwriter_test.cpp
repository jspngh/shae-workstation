#include "xmlwriter_test.h"
#include <QString>
#include <QUuid>
#include <QtWidgets/QtWidgets>
#include <QtTest/QtTest>


XMLWriter_Test::XMLWriter_Test()
{
}

XMLWriter_Test::~XMLWriter_Test()
{

}

void XMLWriter_Test::initTestCase()
{
}

void XMLWriter_Test::cleanupTestCase()
{
}

void XMLWriter_Test::testSimpleDetectionResultXMLWriter()
{
    QString folder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QString fileName = folder.append("/xmltest.xml");

    QFileInfo checkFile(fileName);
    if (checkFile.exists())
        QFile::remove(fileName);

    QList<DetectionResult *> *results = new QList<DetectionResult *>();

    results->push_front(new DetectionResult(QGeoCoordinate(5, 5), 5.5));
    results->push_front(new DetectionResult(QGeoCoordinate(6, 6), 6.6));

    DetectionResultWriter dw = DetectionResultWriter();

    dw.writeDetectionResultToFileXML(fileName, results);

    QList<DetectionResult> expectedResults = QList<DetectionResult>();

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QXmlStreamReader reader(&file);
        while (!reader.isEndDocument()) {
            if (reader.isStartElement() && reader.name() == "DetectionResult") {
                double score, longitude, latitude;
                while (reader.name() != "DetectionResult") {
                    if (reader.isStartElement()) {
                        if (reader.name() == "Score") {
                            score = reader.readElementText().toDouble();
                        } else if (reader.name() == "Latitude") {
                            latitude = reader.readElementText().toDouble();
                        } else if (reader.name() == "Longitude") {
                            longitude = reader.readElementText().toDouble();
                        }
                    }
                    reader.readNext();
                }
                expectedResults.push_back(DetectionResult(QGeoCoordinate(latitude, longitude), score));
            }
            reader.readNext();
        }
    }

    QFile::remove(fileName);

    QVERIFY(results->size() == expectedResults.size());
}

void XMLWriter_Test::testSimpleDetectionResultTXTWriter()
{
    QString folder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QString fileName = folder.append("/txttest.txt");

    QFileInfo checkFile(fileName);
    if (checkFile.exists())
        QFile::remove(fileName);

    QList<DetectionResult *> *results = new QList<DetectionResult *>();

    results->push_front(new DetectionResult(QGeoCoordinate(5, 5), 5.5));
    results->push_front(new DetectionResult(QGeoCoordinate(6, 6), 6.6));

    DetectionResultWriter dw = DetectionResultWriter();

    dw.writeDetectionResultToFileTXT(fileName, results);

    int count  = 0;
    QList<DetectionResult> expectedResults = QList<DetectionResult>();

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            count++;
            if (count > 6) {
                QList<QString> doubles = line.split("\t\t");
                expectedResults.push_back(DetectionResult(
                                              QGeoCoordinate(doubles.at(1).toDouble(), doubles.at(2).toDouble())
                                              , doubles.at(0).toDouble()));
            }
        }
        file.close();
    }

    QFile::remove(fileName);

    QVERIFY(results->size() == expectedResults.size());
}
