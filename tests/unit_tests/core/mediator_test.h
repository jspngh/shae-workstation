#ifndef MEDIATOR_TEST_H
#define MEDIATOR_TEST_H

#include "core/mediator.h"

#include <QObject>
#include <QTest>

class Mediator_Test: public QObject
{
    Q_OBJECT

public:
    Mediator_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testAddMethods();
    void testCountAddSignal();
    void testCountAddSlot();
    void testCount();

private:

};

// class used to emit a signal that will update the value of the listing slots
// the name of signal is "setValue(int)"
class Signal1: public QObject
{
    Q_OBJECT
public:
    Signal1() {}
    ~Signal1() {}

signals:
    void setValue(int a);
};

// class used a dummy slot
class Slot1: public QObject
{
    Q_OBJECT
public:
    Slot1() {}
    ~Slot1() {}

public Q_SLOTS:
    void onSetValue(int a)
    {
        this->value = a;
    }

public:
    int value = 0;
};

#endif // MEDIATOR_TEST_H
