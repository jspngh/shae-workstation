#include "configscriptscontroller.h"

ConfigScriptsController::ConfigScriptsController(QObject *parent) : QObject(parent)
{

}

void ConfigScriptsController::connectToSoloNetwork()
{
    QProcess *proc = new QProcess();
    QString name = "/bin/bash";
    QStringList arg;
    arg << "-c";

    QFile file(":/scripts/connect_to_solo_network.sh");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "script file not found / failed to load: connect_to_solo_network.sh";
        return;
    } else {
        qDebug() << "connecting to solo network";
    }

    arg << file.readAll();
    QString outputPath = standardDataFolder().append("output_solo_network_script.txt");
    arg << outputPath;
    qDebug() << arg;

    if (QFile(outputPath).exists()) {
        QFile(outputPath).remove();
    }
    proc->start(name, arg);
    proc->waitForFinished(-1);
    proc->close();
    QFile outputFile(outputPath);
    if (outputFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&outputFile);
        QString line = in.readAll();
        qDebug() << line;
        if (line.contains(QRegExp("Not connected:")) || line.contains(QRegExp("Error"))) {
            emit notConnectedToSoloNetwork(line);
        } else {
            emit connectedToSoloNetwork();
        }
    }
    outputFile.close();
}


QString ConfigScriptsController::standardDataFolder()
{
    QString folder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    //create folder if not available
    QDir(QDir::root()).mkpath(folder);

    if (!folder.endsWith(QDir::separator()))
        folder.append(QDir::separator());

    return folder;
}


void ConfigScriptsController::setGateway(QString ssid, QString password)
{

    QProcess *proc = new QProcess();
    QString name = "/bin/bash";
    QStringList arg;
    arg << "-c";

    QFile file(":/scripts/set_gateway.sh");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "script file not found / failed to load: set_gateway.sh";
        return;
    } else {
        qDebug() << "setting gateway";
    }

    arg << file.readAll() << ssid << password;
    QString outputPath = standardDataFolder().append("output_set_gateway_script.txt");
    arg << outputPath;
    qDebug() << arg;
    if (QFile(outputPath).exists()) {
        QFile(outputPath).remove();
    }
    proc->start(name, arg);
    proc->waitForFinished(81000);

    proc->close();
    QFile outputFile(outputPath);
    if (outputFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&outputFile);
        QString line = in.readAll();
        qDebug() << line;
        if (line.contains(QRegExp("Error:"))) {
            emit gatewayNotSet(line);
        } else {
            emit gatewaySet();
        }
    }
    outputFile.close();
}
