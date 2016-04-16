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

void XMLWriter_Test::testSimpleDetectionResultWriter()
{
    QString folder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QString fileName = folder.append("/xmltest.xml");
    QList<DetectionResult> results = QList<DetectionResult>();

    results.push_front(DetectionResult(QGeoCoordinate(5, 5), 5.5));
    results.push_front(DetectionResult(QGeoCoordinate(6, 6), 6.6));

    DetectionResultWriter dw = DetectionResultWriter();

    dw.writeDetectionResultToFile(fileName, results);

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

    QVERIFY(results.size() == expectedResults.size());
}
