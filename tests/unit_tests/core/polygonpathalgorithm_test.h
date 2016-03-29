#ifndef POLYGONPATHALGORITHM_TEST_H
#define POLYGONPATHALGORITHM_TEST_H
#include <QString>
#include <QtWidgets/QtWidgets>
#include <QtTest/QtTest>

class PolygonPathAlgorithm_Test : public QObject
{
    Q_OBJECT

public:
    PolygonPathAlgorithm_Test();
    ~PolygonPathAlgorithm_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testPolygonPathAlgorithm();
};

#endif // POLYGONPATHALGORITHM_TEST_H
