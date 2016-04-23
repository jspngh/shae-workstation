#ifndef SIGNALSLOTPERSISTENCETEST_H
#define SIGNALSLOTPERSISTENCETEST_H

#include <QObject>
#include <QtTest>
#include "core/controller.h"
#include "pathlogic/pathalgorithm.h"
#include "pathlogic/simplepathalgorithm.h"
#include "persistence/persistencecontroller.h"
#include "core/mediator.h"

class SignalSlotPersistenceTest : public QObject
{
    Q_OBJECT
public:
    explicit SignalSlotPersistenceTest(QObject *parent = 0);

signals:
    void startSearch(Search*);
    void pathCalculated(Search*);

public slots:
    void initTestCase();
    void testSaveSearch();
    void testSaveDronePaths();

private:
    Controller *c;
    Mediator *m;
    PersistenceController *pc;
};

#endif // SIGNALSLOTPERSISTENCETEST_H
