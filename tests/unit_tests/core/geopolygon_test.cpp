#include "geopolygon_test.h"
#include "pathlogic/geopolygon.h"
#include <QString>
#include <QtWidgets/QtWidgets>
#include <QtTest/QtTest>

GeoPolygon_test::GeoPolygon_test()
{

}

GeoPolygon_test::~GeoPolygon_test()
{

}


void GeoPolygon_test::initTestCase()
{

}

void GeoPolygon_test::cleanUpTestCase()
{

}

void GeoPolygon_test::testDefaultConstructor()
{
    GeoPolygon area = GeoPolygon();
    QList<QGeoCoordinate> coordinates = area.getCoordinates();
    QVERIFY(coordinates.front() == QGeoCoordinate(0.0,0.0));
    coordinates.pop_front();
    QVERIFY(coordinates.front() == (QGeoCoordinate(1.0,0.4)));
    coordinates.pop_front();
    QVERIFY(coordinates.front() == (QGeoCoordinate(1.0,0.6)));
    coordinates.pop_front();
    QVERIFY(coordinates.front() == (QGeoCoordinate(0.0,1.0)));
    coordinates.pop_front();
    QVERIFY(coordinates.isEmpty());

    QVERIFY(area.getMostEastCoordinate() == QGeoCoordinate(0.0,1.0));
    QVERIFY(area.getMostWestCoordinate() == QGeoCoordinate(0.0,0.0));

    QList<QGeoCoordinate> upper = area.getUpperHull();
    QList<QGeoCoordinate> lower = area.getLowerHull();

    QVERIFY(upper.front() == (QGeoCoordinate(0.0,0.0)));
    upper.pop_front();
    QVERIFY(upper.front() == (QGeoCoordinate(1.0,0.4)));
    upper.pop_front();
    QVERIFY(upper.front() == (QGeoCoordinate(1.0,0.6)));
    upper.pop_front();
    QVERIFY(upper.front() == (QGeoCoordinate(0.0,1.0)));
    upper.pop_front();
    QVERIFY(upper.isEmpty());

    QVERIFY(lower.front() == (QGeoCoordinate(0.0,0.0)));
    lower.pop_front();
    QVERIFY(lower.front() == (QGeoCoordinate(0.0,1.0)));
    lower.pop_front();
    QVERIFY(upper.isEmpty());

}

void GeoPolygon_test::testConstructor()
{
    //tODO
}

void GeoPolygon_test::testFromHull()
{
    QList<QGeoCoordinate> upper = QList<QGeoCoordinate>();
    upper.push_back(QGeoCoordinate(0.0,0.0));
    upper.push_back(QGeoCoordinate(4.0,0.0001));
    upper.push_back(QGeoCoordinate(2.0,1.9));
    upper.push_back(QGeoCoordinate(1.0,3.0));

    QList<QGeoCoordinate> lower = QList<QGeoCoordinate>();
    lower.push_back(QGeoCoordinate(0.0,0.0));
    lower.push_back(QGeoCoordinate(-1.0,1.0));
    lower.push_back(QGeoCoordinate(-1.1,2.0));
    lower.push_back(QGeoCoordinate(1.0,3.0));

    QList<QGeoCoordinate> coordinates = GeoPolygon::fromHull(upper, lower);
    QVERIFY(coordinates.front() == QGeoCoordinate(0.0,0.0));
    coordinates.pop_front();
    QVERIFY(coordinates.front() == QGeoCoordinate(4.0,0.0001));
    coordinates.pop_front();
    QVERIFY(coordinates.front() == QGeoCoordinate(2.0,1.9));
    coordinates.pop_front();
    QVERIFY(coordinates.front() == QGeoCoordinate(1.0,3.0));
    coordinates.pop_front();
    QVERIFY(coordinates.front() == QGeoCoordinate(-1.1,2.0));
    coordinates.pop_front();
    QVERIFY(coordinates.front() == QGeoCoordinate(-1.0,1.0));
    coordinates.pop_front();
    QVERIFY(coordinates.isEmpty());


}

void GeoPolygon_test::testGetBoundingQGeoRectangle()
{
    //TODO
}

void GeoPolygon_test::testCrossProduct()
{

}

void GeoPolygon_test::testCompare()
{
    auto c1 = QGeoCoordinate(0.0,0.0);
    auto c2 = QGeoCoordinate(0.0,0.0);
    QVERIFY(GeoPolygon::compare(c1,c2) == false);
}
void GeoPolygon_test::testCompare2()
{
    auto c1 = QGeoCoordinate(1.0,0.0);
    auto c2 = QGeoCoordinate(0.0,0.0);
    QVERIFY(GeoPolygon::compare(c1,c2) == false);
}

void GeoPolygon_test::testCompare3()
{
    auto c1 = QGeoCoordinate(0.0,0.0);
    auto c2 = QGeoCoordinate(1.0,0.0);
    QVERIFY(GeoPolygon::compare(c1,c2) == true);
}

void GeoPolygon_test::testCompare4()
{
    auto c1 = QGeoCoordinate(0.0,0.0);
    auto c2 = QGeoCoordinate(0.0,1.0);
    QVERIFY(GeoPolygon::compare(c1,c2) == true);
}

void GeoPolygon_test::testCompare5()
{
    auto c1 = QGeoCoordinate(0.0,1.0);
    auto c2 = QGeoCoordinate(0.0,0.0);
    QVERIFY(GeoPolygon::compare(c1,c2) == false);
}

void GeoPolygon_test::testCompare6()
{
    auto c1 = QGeoCoordinate(1.0,-1.0);
    auto c2 = QGeoCoordinate(0.0,0.0);
    QVERIFY(GeoPolygon::compare(c1,c2) == true);
}


void GeoPolygon_test::testCompareLatitude()
{
    auto c1 = QGeoCoordinate(0.0,0.0);
    auto c2 = QGeoCoordinate(0.0,0.0);
    QVERIFY(GeoPolygon::compareLatitude(c1,c2) == false);
}
void GeoPolygon_test::testCompareLatitude2()
{
    auto c1 = QGeoCoordinate(1.0,0.0);
    auto c2 = QGeoCoordinate(0.0,0.0);
    QVERIFY(GeoPolygon::compareLatitude(c1,c2) == false);
}

void GeoPolygon_test::testCompareLatitude3()
{
    auto c1 = QGeoCoordinate(0.0,0.0);
    auto c2 = QGeoCoordinate(1.0,0.0);
    QVERIFY(GeoPolygon::compareLatitude(c1,c2) == true);
}

void GeoPolygon_test::testCompareLatitude4()
{
    auto c1 = QGeoCoordinate(0.0,0.0);
    auto c2 = QGeoCoordinate(0.0,1.0);
    QVERIFY(GeoPolygon::compareLatitude(c1,c2) == true);
}

void GeoPolygon_test::testCompareLatitude5()
{
    auto c1 = QGeoCoordinate(0.0,1.0);
    auto c2 = QGeoCoordinate(0.0,0.0);
    QVERIFY(GeoPolygon::compareLatitude(c1,c2) == false);
}

void GeoPolygon_test::testCompareLatitude6()
{
    auto c1 = QGeoCoordinate(1.0,-1.0);
    auto c2 = QGeoCoordinate(0.0,0.0);
    QVERIFY(GeoPolygon::compareLatitude(c1,c2) == false);
}


void GeoPolygon_test::testIsValid()
{

}

void GeoPolygon_test::testToSring()
{

}
