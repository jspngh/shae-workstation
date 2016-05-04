#ifndef PATHALGORITHM_TEST_H
#define PATHALGORITHM_TEST_H
#include <QString>
#include <QtTest/QtTest>
#include "pathlogic/pathalgorithm.h"

class Pathalgorithm_Test : public QObject
{
    Q_OBJECT

public:
    Pathalgorithm_Test();
    ~Pathalgorithm_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testConstructor1();
    void testConstructor2();
    void testSetMediator();
    void testGoDirectionWest();
    void testGoDirectionEast();
    void testGoDirectionBetween();
};

#endif // PATHALGORITHM_TEST_H
