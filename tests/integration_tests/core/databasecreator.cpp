#include "databasecreator.h"
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QStandardPaths>
#include <QSqlQuery>
#include <QSql>
#include <QSqlError>

DatabaseCreator::DatabaseCreator()
{

}

void DatabaseCreator::initDatabase()
{
    bool dbNotCreatedYet = false;

    qDebug() << databaseLocation();
    // Make sure the file exists
    QFileInfo checkFile(databaseLocation());
    if (!checkFile.exists() || !checkFile.isFile()) {
        // If not, create a file in which we will create the database
        QFile databaseFile(databaseLocation());
        databaseFile.open(QIODevice::ReadWrite);
        databaseFile.close();
        dbNotCreatedYet = true;
    }

    // Open database
    projectShaeDatabase = QSqlDatabase::addDatabase("QSQLITE");
    projectShaeDatabase.setDatabaseName(databaseLocation());

    if (!projectShaeDatabase.open())
        qDebug() << projectShaeDatabase.lastError();
    else
        qDebug() << "Database connection successfully setup.";

    if (dbNotCreatedYet) {
        createDatabase();
    }
}

QString DatabaseCreator::databaseLocation()
{
    QString folder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    //create folder if not available
    QDir(QDir::root()).mkpath(folder);

    if (!folder.endsWith(QDir::separator()))
        folder.append(QDir::separator());

    QString name = "database.sqlite";

    return folder.append(name);
}

void DatabaseCreator::createDatabase()
{
    QFile sqlScheme(":/db/createTables.sql");
    if (sqlScheme.open(QIODevice::ReadOnly)) {
        QSqlQuery query(projectShaeDatabase);
        QStringList queryStrings = QTextStream(&sqlScheme).readAll().split(';');
        // Can't execute several queries at once, so split them
        // and execute them one by one.
        Q_FOREACH(QString queryString, queryStrings) {
            if (!query.exec(queryString))
                qDebug() << "Could not issue command: " << queryString;
        }
    } else {
        qDebug() << "Error opening file to create database";
    }
}

void DatabaseCreator::removeDatabase()
{
    QString location = databaseLocation();
    QFileInfo checkFile(location);
    if(checkFile.exists())
        QFile::remove(databaseLocation());
}

