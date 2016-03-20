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


void Mediator_Test::testConnects()
{
    Signal1 signalObj;
    Slot1 slotObj;

    // inform mediator of existing signal and slot
    this->mediator.addSignal(&signalObj, SIGNAL(setValue(int)), QString("setValue(int)"));
    this->mediator.addSlot(&slotObj, SLOT(onSetValue(int)), QString("setValue(int)"));

    // inspect the connection
    QSignalSpy spy(&signalObj, SIGNAL(setValue(int)));

    // trigger signal
    emit signalObj.setValue(10);

    // make sure the signal was emitted exactly one time
    QCOMPARE(spy.count(), 1);

    // take the first signal
    QList<QVariant> arguments = spy.takeFirst();

    // verify the first argument is an integer
    QVERIFY(arguments.at(0).type() == QVariant::Int);
}

void Mediator_Test::testAddMethods()
{
    int v = 10;

    Signal1 signalObj;
    Slot1 slotObj;

    // inform mediator of existing signal and slot
    this->mediator.addSignal(&signalObj, SIGNAL(setValue(int)), QString("setValue(int)"));
    this->mediator.addSlot(&slotObj, SLOT(onSetValue(int)), QString("setValue(int)"));

    // trigger signal
    emit signalObj.setValue(v);

    // verify is slot was executed
    QVERIFY(slotObj.value == v);
}

void  Mediator_Test::testCountAddSignal()
{
    Signal1 signalObj;
    int count = this->mediator.addSignal(&signalObj, SIGNAL(setValue(int)), QString("setValue(int)"));

    // verify that there is no matching slot when the signal was added to the mediator
    QVERIFY(count == 0);
}

void  Mediator_Test::testCountAddSlot()
{
    Slot1 slotObj;
    int count = this->mediator.addSlot(&slotObj, SLOT(onSetValue(int)), QString("setValue(int)"));

    // verify that there is no matching signal when the slot was added to the mediator
    QVERIFY(count == 0);
}

void  Mediator_Test::testCount()
{
    Signal1 signalObj;
    Slot1 slotObj;

    this->mediator.addSignal(&signalObj, SIGNAL(setValue(int)), QString("setValue(int)"));
    int count = this->mediator.addSlot(&slotObj, SLOT(onSetValue(int)), QString("setValue(int)"));

    // verify that there is a matching slot when the signal was added to the mediator
    QVERIFY(count == 1);
}
