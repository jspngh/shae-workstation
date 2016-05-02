#include "configscriptscontroller.h"

ConfigScriptsController::ConfigScriptsController(QObject *parent) : QObject(parent)
{

}

void ConfigScriptsController::connectToSoloNetwork()
{
    QProcess *process = new QProcess();
    //process->start("/bin/bash", QStringList() << "qrc:/scripts/test");
    process->setWorkingDirectory("../../src/scripts");
    process->start("./connect_to_solo_network.sh");
    process->waitForFinished(-1);
    QString output(process->readAll());
    //QString result = output.split(QRegExp("[\r\n]"), QString::SkipEmptyParts).last();

    if (output.contains(QRegExp("Not connected:")))
    {
        QString error = output.split(QRegExp("Not connected:"), QString::SkipEmptyParts).last();
        emit notConnectedToSoloNetwork(error);
    } else {
        emit connectedToSoloNetwork();
    }
}

void ConfigScriptsController::setGateway(QString ssid, QString password)
{
    QProcess *process = new QProcess();
    //process->start("/bin/bash", QStringList() << "qrc:/scripts/test");
    process->setWorkingDirectory("../../src/scripts");
    process->start("./set_gateway.sh " + ssid + " " + password);
    process->waitForFinished(81000);
    QString output(process->readAll());
    QString result = output.split(QRegExp("[\r\n]"), QString::SkipEmptyParts).last();

    if (result.contains(QRegExp("Error:")))
    {
        emit gatewayNotSetted(result);
    } else {
        emit gatewaySetted();
    }
}
