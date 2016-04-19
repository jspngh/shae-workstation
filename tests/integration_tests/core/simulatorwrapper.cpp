#include "simulatorwrapper.h"

SimulatorWrapper::SimulatorWrapper()
{

}

void SimulatorWrapper::startSimulator()
{
    QString program = "python";
    QStringList arguments;
    qDebug() << "opening simulator, this takes some time...";
    arguments << "../../../drone/simulator/src/simulator.py";
    simulatorProcess = new QProcess(this);

    simulatorProcess->start(program, arguments);
    //QTest::qWait(25000);

    qDebug() << "simulator opened";

}

void SimulatorWrapper::stopSimulator()
{
    simulatorProcess->terminate();
    simulatorProcess->waitForFinished();
    simulatorProcess->close();
    qDebug() << "Closed simulator";
    QTest::qWait(500);

//    QString program = "kill_simulator.sh";
//    QProcess *killProcess = new QProcess(this);
//    killProcess->start(program);

    delete simulatorProcess;
}
