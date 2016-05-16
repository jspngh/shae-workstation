#include "resetscriptcontroller.h"
#include <QProcess>
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>
#include <QString>
#include <QDebug>

ResetScriptController::ResetScriptController(QObject *parent): QObject(parent)
{

}

void ResetScriptController::reset()
{
    qDebug() << "resetting drone services...";
    QString configFolder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QString rsaFileName = "shae_rsa";
    QString scriptFileName = "reset_services.sh";

    // create folder if not available
    QDir(QDir::root()).mkpath(configFolder);

    if (!configFolder.endsWith(QDir::separator()))
        configFolder.append(QDir::separator());

    QString keyPath = configFolder + rsaFileName;
    QString scriptPath = configFolder + scriptFileName;
    QFile rsaKey(keyPath);
    QFile resetScript(scriptPath);

    // if the file already exists nothing needs to be done anymore
    // in general this function only needs to copy the file once, the first the time the application runs
    if (!rsaKey.exists()) {
        QFile srcFile(":/scripts/shae_rsa");
        srcFile.open(QIODevice::ReadOnly);
        QTextStream in(&srcFile);
        rsaKey.open(QIODevice::WriteOnly);
        QTextStream out(&rsaKey);
        out << in.readAll();

        /* Close the files */
        rsaKey.close();
        srcFile.close();

        /* Set correct permissions */
        rsaKey.setPermissions(QFile::ReadOwner);
    }
    if (!resetScript.exists()) {
        QFile scriptSrcFile(":/scripts/reset_services.sh");
        scriptSrcFile.open(QIODevice::ReadOnly);
        QTextStream in(&scriptSrcFile);
        resetScript.open(QIODevice::WriteOnly);
        QTextStream out(&resetScript);
        out << in.readAll();

        /* Close the files */
        resetScript.close();
        scriptSrcFile.close();

        /* Set correct permissions */
        resetScript.setPermissions(QFile::ExeOwner | QFile::ReadOwner | QFile::WriteOwner);
    }

    QProcess *proc = new QProcess();
    QStringList arg;
    arg << keyPath;
    proc->start(scriptPath, arg);
    proc->waitForFinished();
    proc->close();
    qDebug() << "resetting drone services finished...";
    emit resetSuccessful();
}


