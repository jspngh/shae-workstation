#include <QString>
#include <QtWidgets/QtWidgets>
#include <QtTest/QtTest>
#include "core/communication.h"
#include "core/waypointplanning.h"

class Frontend_Test : public QObject
{
    Q_OBJECT

public:
    Frontend_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
    void testCase2();
    void testCase3();
    void testSimplePathAlgorithm();
};

Frontend_Test::Frontend_Test()
{
}

void Frontend_Test::initTestCase()
{
}

void Frontend_Test::cleanupTestCase()
{
}

void Frontend_Test::testCase1()
{
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
}

void Frontend_Test::testCase2()
{
    QString str = "Hello";
    QVERIFY(str.toUpper() == "HELLO");
}

void Frontend_Test::testCase3()
{
    Communication* comm = new Communication();
    QVERIFY(comm->send_data() == "test");


}

/*! This tests the SimplePathAlgorithm in a basic example. This is not an exhaustive test.

*/
void Frontend_Test::testSimplePathAlgorithm()
{
    RectangleArea area = RectangleArea();
    area.northEast= Coordinate(10.0,10.0);
    area.northWest= Coordinate(10.0,0.0);
    area.southEast= Coordinate(0.0,10.0);
    area.southWest= Coordinate(0.0,0.0);
    Coordinate start = Coordinate(2.0,2.0);
    SimplePathAlgorithm algorithm = SimplePathAlgorithm(start);

    std::list<Coordinate> calculatedList = algorithm.calculateWaypoints(area, 2.0);
    std::list<Coordinate> testList = std::list<Coordinate>();

    testList.push_back(Coordinate(0.0,0.0));
    testList.push_back(Coordinate(10.0,0.0));
    testList.push_back(Coordinate(10.0,2.0));
    testList.push_back(Coordinate(0.0,2.0));
    testList.push_back(Coordinate(0.0,4.0));
    testList.push_back(Coordinate(10.0,4.0));
    testList.push_back(Coordinate(10.0,6.0));
    testList.push_back(Coordinate(0.0,6.0));
    testList.push_back(Coordinate(0.0,8.0));
    testList.push_back(Coordinate(10.0,8.0));
    testList.push_back(Coordinate(10.0,10.0));
    testList.push_back(Coordinate(0.0,10.0));

//Do the checks
    int listSize = 12;
    for(int i=0; i<listSize; i++){
        Coordinate calculated = calculatedList.front();
        Coordinate test = testList.front();

        calculatedList.pop_front();
        testList.pop_front();

        //vergelijk
        QVERIFY(calculated.latitude == test.latitude);
        QVERIFY(calculated.longitude == test.longitude);


    }




}

QTEST_MAIN(Frontend_Test)
#include "frontend_test.moc"
