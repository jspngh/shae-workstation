#ifndef SIMPLEPATHALGORITHM_TEST_H
#define SIMPLEPATHALGORITHM_TEST_H
#include <QString>
#include <QtWidgets/QtWidgets>
#include <QtTest/QtTest>

/*!
 * \brief The SimplePathAlgorithm_Test class tests the simple boustrophedon waypoint planning algorithm.
 */
class SimplePathAlgorithm_Test : public QObject
{
    Q_OBJECT

public:
    SimplePathAlgorithm_Test();
    ~SimplePathAlgorithm_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    /*! \brief This tests the SimplePathAlgorithm in a basic example.
     *  The first waypoint is in the lower left corner. The starting point is
     *  inside the search area.
     */
    void testSimplePathAlgorithm();

    /*!
     * \brief Almost the same test as the previous one.
     * Now the width of the area is not an integer times the visionWidth of the
     * drone. Also, the starting point of the drone is way outside the search
     * area, instead of in the search area as is the case in the previous test.
     * The first wayoint is in the the upperright corner.
     */
    void testSimplePathAlgorithm2();
    void testSimplePathAlgorithm3();

    void testSimplePathAlgorithmPolygon();
    void testSimplePathAlgorithmWithMultipleDrones();
    void testSimplePathAlgorithmWithMultipleDrones2();

    void testSimplePathAlgorithmPolygonMultipleDrones();
};

#endif // SIMPLEPATHALGORITHM_TEST_H

