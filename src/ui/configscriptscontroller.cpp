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
    arg << " >> ";
    QString outputPath = standardDataFolder().append("output_solo_network_script.txt");
    arg << outputPath;
    if(QFile(outputPath).exists())
    {
        QFile(outputPath).remove();
    }
    proc->start(name, arg);
    proc->waitForFinished(-1);

    proc->close();
    QFile outputFile(outputPath);
    if(outputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&outputFile);
         while (!in.atEnd())
         {
            QString line = in.readLine();
            qDebug() << line;
            if(line.contains(QRegExp("Not connected:")))
            {
                QString error = line.split(QRegExp("Not connected:"), QString::SkipEmptyParts).last();
                emit notConnectedToSoloNetwork(error);
            }else
            {
                emit connectedToSoloNetwork();
            }
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
    QProcess *process = new QProcess();
    //process->start("/bin/bash", QStringList() << "qrc:/scripts/test");
    process->setWorkingDirectory("../../src/scripts");
    process->start("./set_gateway.sh " + ssid + " " + password);
    process->waitForFinished(81000);
    QString output(process->readAll());
    QString result = output.split(QRegExp("[\r\n]"), QString::SkipEmptyParts).last();

    if (result.contains(QRegExp("Error:")))
    {
        emit gatewayNotSet(result);
    } else {
        emit gatewaySet();
    }
}
