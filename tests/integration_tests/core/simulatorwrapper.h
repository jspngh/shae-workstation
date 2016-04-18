#ifndef SIMULATORWRAPPER_H
#define SIMULATORWRAPPER_H
#include <QProcess>
#include <QtTest>

class SimulatorWrapper : QObject
{
    Q_OBJECT

public:
    SimulatorWrapper();
    void startSimulator();
    void stopSimulator();


    QProcess *simulatorProcess;
};

#endif // SIMULATORWRAPPER_H
