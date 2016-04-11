#include "simulatorwrapper.h"

SimulatorWrapper::SimulatorWrapper()
{

}

void SimulatorWrapper::startSimulator()
{
    QString program = "python";
    QStringList arguments;
    qDebug() << "opening simulator";
    arguments << "../../../drone/simulator/src/simulator.py";
    simulatorProcess = new QProcess(this);

    simulatorProcess->start(program, arguments);
    QTest::qWait(20000);
    qDebug() << "simulator opened";

}

void SimulatorWrapper::stopSimulator()
{
    simulatorProcess->terminate();
    simulatorProcess->waitForFinished();
    simulatorProcess->close();

    delete simulatorProcess;
}
