#include "mediator.h"
#include <QDebug>

Mediator::Mediator(QObject *parent)
    : QObject(parent)
{
    qRegisterMetaType<DroneStatus>("DroneStatus");
}

int Mediator::addSignal(QObject *sender, const char *signal, QString signalName)
{
    int count = 0;
    this->mutex.lock();

    QList<Element>::iterator i;
    // search for a slot listing to the signal
    for (i = this->slotList.begin(); i != this->slotList.end(); ++i) {
        if (i->signalName == signalName) {
            // found a slot in the slotList that implements slot for the signal
            // connect the signal and the found slot
            QObject::connect(sender, signal, i->object, i->method);
            ++count;
            qDebug() << "Signal added: " << signalName;
        }
    }
    // store an Element object holding information about the signal.
    // This is necessary in case a new slots wants to connect to the same signal.
    this->signalList.append(Element(sender, signal, signalName));

    // connect slot
    QObject::connect(sender, SIGNAL(destroyed(QObject *)), this, SLOT(onSenderObjectDestroyed(QObject *)));

    this->mutex.unlock();

    return count;
}

int Mediator::addSlot(QObject *receiver, const char *slot, QString signalName)
{
    int count = 0;

    this->mutex.lock();

    QList<Element>::iterator i;
    // search for a signal emitting the desired signal
    for (i = this->signalList.begin(); i != this->signalList.end(); ++i) {
        if (i->signalName == signalName) {
            // found a signal in the signaltList that emits the desired signal
            // connect the found signal and the slot
            QObject::connect(i->object, i->method, receiver, slot);
            ++count;
            qDebug() << "Slot added for signal: " << signalName;
        }
    }
    // store an Element object holding information about the signal.
    // This is necessary in case a new slots wants to connect to the same signal.
    this->slotList.append(Element(receiver, slot, signalName));

    // connect slot
    QObject::connect(receiver, SIGNAL(destroyed(QObject *)), this, SLOT(onReceiverObjectDestroyed(QObject *)));

    this->mutex.unlock();

    return count;
}

void Mediator::onReceiverObjectDestroyed(QObject *obj)
{
    mutex.lock();
    for (int i = 0; i < this->slotList.length(); i++) {
        if (this->slotList.at(i).object == obj) {
            slotList.removeAt(i);
        }
    }
    mutex.unlock();
}

void Mediator::onSenderObjectDestroyed(QObject *obj)
{
    mutex.lock();
    for (int i = 0; i < this->signalList.length(); i++) {
        if (this->signalList.at(i).object == obj) {
            signalList.removeAt(i);
        }
    }
    mutex.unlock();
}

