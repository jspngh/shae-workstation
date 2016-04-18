#include <QtTest/QtTest>
#include <QString>
#include "generaldao_test.h"
#include "persistence/generaldao.h"

GeneralDAO_Test::GeneralDAO_Test()
{

}

GeneralDAO_Test::~GeneralDAO_Test()
{
}

void GeneralDAO_Test::initTestCase()
{
}

void GeneralDAO_Test::cleanupTestCase()
{
}

void GeneralDAO_Test::testUncypherGeneralDAO()
{
    QString testString = QString("5-5:6-6:7-7:8-8");
    GeneralDAO generaldao = GeneralDAO();
    QList<QGeoCoordinate> returnList = generaldao.uncypherPathString(testString);
    QVERIFY(returnList.size() == 4);
    double i = 5;
    for (QGeoCoordinate coordinate : returnList) {
        QVERIFY(coordinate.longitude() == i);
        QVERIFY(coordinate.latitude() == i);
        i++;
    }
}

void GeneralDAO_Test::testUncypherEmptyStringGeneralDAO()
{
    QString testString = QString("5-5:6-6:7-7:8-8");
    GeneralDAO generaldao = GeneralDAO();
    QVERIFY(generaldao.uncypherPathString(testString).empty());
}
