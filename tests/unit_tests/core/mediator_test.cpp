#include "mediator_test.h"

Mediator_Test::Mediator_Test()
{

}

void Mediator_Test::initTestCase()
{

}

void Mediator_Test::cleanupTestCase()
{

}

void Mediator_Test::testAddMethods()
{
    Mediator mediator;
    int v = 10;
    Signal1 signalObj;
    Slot1 slotObj;
    mediator.addSignal(&signalObj, SIGNAL(setValue(int)), QString("setValue(int)"));
    mediator.addSlot(&slotObj, SLOT(onSetValue(int)), QString("setValue(int)"));
    emit signalObj.setValue(v);

    QVERIFY(slotObj.value == v);
}

void  Mediator_Test::testCountAddSignal()
{
    Mediator mediator;
    Signal1 signalObj;
    int count = mediator.addSignal(&signalObj, SIGNAL(setValue(int)), QString("setValue(int)"));
    QVERIFY(count == 0);
}

void  Mediator_Test::testCountAddSlot()
{
    Mediator mediator;
    Slot1 slotObj;
    int count = mediator.addSlot(&slotObj, SLOT(onSetValue(int)), QString("setValue(int)"));
    QVERIFY(count == 0);
}

void  Mediator_Test::testCount()
{
    Mediator mediator;
    Signal1 signalObj;
    Slot1 slotObj;
    mediator.addSignal(&signalObj, SIGNAL(setValue(int)), QString("setValue(int)"));
    int count = mediator.addSlot(&slotObj, SLOT(onSetValue(int)), QString("setValue(int)"));
    QVERIFY(count == 1);
}
