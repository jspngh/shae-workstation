#ifndef SIGNALSLOTPERSISTENCETEST_H
#define SIGNALSLOTPERSISTENCETEST_H

#include <QObject>
#include <QtTest>
#include "persistence/persistencecontroller.h"
#include "core/mediator.h"

class SignalSlotPersistenceTest : public QObject
{
    Q_OBJECT
public:
    explicit SignalSlotPersistenceTest(QObject *parent = 0);
    void initTestCase();
    void testSaveSearch();

signals:
    void startSearch(Search*);

public slots:

private:
    Mediator *m;
    PersistenceController *pc;
};

#endif // SIGNALSLOTPERSISTENCETEST_H
