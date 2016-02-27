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
    void testSimplePathAlgorithm2();
    void testSimplePathAlgorithm3();
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

/*! \brief This tests the SimplePathAlgorithm in a basic example.
 *  The first waypoint is in the lower left corner. The starting point is inside the search area.

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

    //Create testlist
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
    double epsilon = 0.000001;
    int listSize = 12;
    for(int i=0; i<listSize; i++){
        Coordinate calculated = calculatedList.front();
        Coordinate test = testList.front();

        calculatedList.pop_front();
        testList.pop_front();

        //compare
        QVERIFY(abs(calculated.latitude- test.latitude)<epsilon);
        QVERIFY(abs(calculated.longitude- test.longitude)<epsilon);

    }




}

/*!
 * \brief Almost the same test as the previous one.
 * Now the width of the area is not an integer times the visionWidth of the drone.
 * Also, the starting point of the drone is way outside the search area, instead of in the search area as is the case in the previous test. The first wayoint is in the the upperright corner.
 */

void Frontend_Test::testSimplePathAlgorithm2()
{

    //initiate area, start point and algorithm.
    RectangleArea area = RectangleArea();
    area.northEast= Coordinate(1.0,1.0);
    area.northWest= Coordinate(1.0,-1.0);
    area.southEast= Coordinate(-1.0,1.0);
    area.southWest= Coordinate(-1.0,-1.0);
    Coordinate start = Coordinate(20.0,20.0);
    SimplePathAlgorithm algorithm = SimplePathAlgorithm(start);

    std::list<Coordinate> calculatedList = algorithm.calculateWaypoints(area, 0.3);

    //Create testlist
    std::list<Coordinate> testList = std::list<Coordinate>();
    testList.push_back(Coordinate(1.0,1.0));
    testList.push_back(Coordinate(-1.0,1.0));
    testList.push_back(Coordinate(-1.0,0.7));
    testList.push_back(Coordinate(1.0,0.7));
    testList.push_back(Coordinate(1.0,0.4));
    testList.push_back(Coordinate(-1.0,0.4));
    testList.push_back(Coordinate(-1.0,0.1));
    testList.push_back(Coordinate(1.0,0.1));
    testList.push_back(Coordinate(1.0,-0.2));
    testList.push_back(Coordinate(-1.0,-0.2));
    testList.push_back(Coordinate(-1.0,-0.5));
    testList.push_back(Coordinate(1.0,-0.5));
    testList.push_back(Coordinate(1.0,-0.8));
    testList.push_back(Coordinate(-1.0,-0.8));
    testList.push_back(Coordinate(-1.0,-1.1));
    testList.push_back(Coordinate(1.0,-1.1));


//Do the checks
    double epsilon = 0.000001;
    int listSize = testList.size();
    for(int i=0; i<listSize; i++){
        Coordinate calculated = calculatedList.front();
        Coordinate test = testList.front();

        calculatedList.pop_front();
        testList.pop_front();

        //Compare
        QVERIFY(abs(calculated.latitude- test.latitude)<epsilon);
        QVERIFY(abs(calculated.longitude- test.longitude)<epsilon);


    }

}

void Frontend_Test::testSimplePathAlgorithm3()
{

        //initiate area, start point and algorithm.
        RectangleArea area = RectangleArea();
        area.northEast= Coordinate(1.0,1.0);
        area.northWest= Coordinate(1.0,-1.0);
        area.southEast= Coordinate(-1.0,1.0);
        area.southWest= Coordinate(-1.0,-1.0);
        Coordinate start = Coordinate(-20.0,20.0);
        SimplePathAlgorithm algorithm = SimplePathAlgorithm(start);

        std::list<Coordinate> calculatedList = algorithm.calculateWaypoints(area, 0.6);

        //Create testlist
        std::list<Coordinate> testList = std::list<Coordinate>();
        testList.push_back(Coordinate(-1.0,1.0));
        testList.push_back(Coordinate(1.0,1.0));
        testList.push_back(Coordinate(1.0,0.4));
        testList.push_back(Coordinate(-1.0,0.4));
        testList.push_back(Coordinate(-1.0,-0.2));
        testList.push_back(Coordinate(1.0,-0.2));
        testList.push_back(Coordinate(1.0,-0.8));
        testList.push_back(Coordinate(-1.0,-0.8));
        testList.push_back(Coordinate(-1.0,-1.4));
        testList.push_back(Coordinate(1.0,-1.4));


    //Do the checks
        double epsilon = 0.000001;
        int listSize = testList.size();
        for(int i=0; i<listSize; i++){
            Coordinate calculated = calculatedList.front();
            Coordinate test = testList.front();

            calculatedList.pop_front();
            testList.pop_front();

            //Compare
            QVERIFY(abs(calculated.latitude- test.latitude)<epsilon);
            QVERIFY(abs(calculated.longitude- test.longitude)<epsilon);


        }



}

QTEST_MAIN(Frontend_Test)
#include "frontend_test.moc"
