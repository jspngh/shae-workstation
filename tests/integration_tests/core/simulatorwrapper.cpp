#include "simulatorwrapper.h"

SimulatorWrapper::SimulatorWrapper()
{

}

void SimulatorWrapper::startSimulator()
{
    QString program = "python2";
    QStringList arguments;
    qDebug() << "opening simulator, this takes some time...";
    arguments << "../../../drone/src/simulator/simulator.py";
    simulatorProcess = new QProcess(this);
    simulatorProcess->start(program, arguments);

    qDebug() << "simulator opened";

}

void SimulatorWrapper::stopSimulator()
{
    simulatorProcess->terminate();
    simulatorProcess->waitForFinished();
    simulatorProcess->close();
    qDebug() << "Closed simulator";
    QTest::qWait(500);

    delete simulatorProcess;
}
