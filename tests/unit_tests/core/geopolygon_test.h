#ifndef GEOPOLYGON_TEST_H
#define GEOPOLYGON_TEST_H

#include <QObject>

class GeoPolygon_test: public QObject
{
    Q_OBJECT

public:
    GeoPolygon_test();
    ~GeoPolygon_test();

private Q_SLOTS:
    void initTestCase();
    void cleanUpTestCase();

    void testDefaultConstructor();
    void testConstructor();
    void testFromHull();
    void testGetBoundingQGeoRectangle();
    void testCrossProduct();
    void testCompare();
    void testCompare2();
    void testCompare3();
    void testCompare4();
    void testCompare5();
    void testCompare6();
    void testCompareLatitude();
    void testCompareLatitude2();
    void testCompareLatitude3();
    void testCompareLatitude4();
    void testCompareLatitude5();
    void testCompareLatitude6();
    void testIsValid();
    void testToSring();
};

#endif // GEOPOLYGON_TEST_H
