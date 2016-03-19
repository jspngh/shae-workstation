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
    int v = 10;
    Signal1 signalObj;
    Slot1 slotObj;
    Mediator::get().addSignal(&signalObj, SIGNAL(setValue(int)), QString("setValue(int)"));
    Mediator::get().addSlot(&slotObj, SLOT(onSetValue(int)), QString("setValue(int)"));
    emit signalObj.setValue(v);

    QVERIFY(slotObj.value == v);
}

void  Mediator_Test::testCountAddSignal()
{
    Signal1 signalObj;
    int count = Mediator::get().addSignal(&signalObj, SIGNAL(setValue(int)), QString("setValue(int)"));
    QVERIFY(count == 0);
}

void  Mediator_Test::testCountAddSlot()
{
    Slot1 slotObj;
    int count = Mediator::get().addSlot(&slotObj, SLOT(onSetValue(int)), QString("setValue(int)"));
    QVERIFY(count == 0);
}

void  Mediator_Test::testCount()
{
    Signal1 signalObj;
    Slot1 slotObj;
    Mediator::get().addSignal(&signalObj, SIGNAL(setValue(int)), QString("setValue(int)"));
    int count = Mediator::get().addSlot(&slotObj, SLOT(onSetValue(int)), QString("setValue(int)"));
    QVERIFY(count == 1);
}
