#ifndef DATABASECREATOR_H
#define DATABASECREATOR_H

#include <QObject>
#include <QGeoCoordinate>
#include <QUuid>
#include <QSql>
#include <QSqlDatabase>

class DatabaseCreator
{
public:
    DatabaseCreator();
    //! \brief Initializes the database (sets the projectShaeDatabase-property).
    void initDatabase();
    //! \brief Returns the path to the database file.
    QString databaseLocation();
    //!  \brief Create the database.
    void createDatabase();
private:
    QSqlDatabase projectShaeDatabase;
};

#endif // DATABASECREATOR_H
