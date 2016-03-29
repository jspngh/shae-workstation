#include "searchdao.h"
#include <QDebug>

SearchDAO::SearchDAO()
{
}

SearchDAO::SearchDAO(QSqlDatabase* projectShaeDatabase){
    this->projectShaeDatabase = projectShaeDatabase;
}

Search SearchDAO::dbSaveSearch(Search search){
    if(projectShaeDatabase->open())
    {
        qDebug() << "database connection succes" ;
    } else {
        qDebug() << "database connection error";
    }

    // todo check if args are ok
    QSqlQuery query;
    query.prepare("INSERT INTO searches (searchID, start) "
                  "VALUES (:searchID, :start)");
    query.bindValue(":searchID", search.getSearchID());
    query.bindValue(":start", search.getStartTime());
    if(query.exec())
    {
       qDebug() << "insert succes";
    }
    else
    {
       qDebug() << "addsearch error:  "
                << query.lastError();
    }
    return search;
}

Search SearchDAO::dbRetrieveSearch(QUuid searchId){
    QSqlQuery query;
    Search search;
    query.prepare("SELECT * FROM searches WHERE searchID = (:searchID)");
    query.bindValue(":searchID", searchId);
    if(query.exec())
    {
        if (query.next())
        {
            search = Search(QUuid(query.value(0).toString()), query.value(1).toTime());
            /*QList <Drone> drones = QList<Drone>;
            QSqlQuery queryDrones;
            queryDrones.prepare("SELECT droneID FROM dronessearches WHERE searchID = (:searchID)");
            queryDrones.bindValue(":searchID", searchId);
            if(queryDrones.exec())
            {
                while(queryDrones.next())
                {
                    QSqlQuery queryDrone;
                    queryDrone.prepare("SELECT * FROM drones WHERE droneID = (:droneID)");
                    queryDrone.bindValue(":droneID", queryDrones.value(0));
                    if(queryDrone.exec())
                    {
                            if(queryDrone.next())
                                drones.append(Drone(QUuid(queryDrone.value(0).,queryDrone.value(1))));
                    }
                    else
                    {
                        qDebug() << "getdrone from getDroneSearches from getsearch error: "
                                 << queryDrones.lastError();
                    }
                }
            }
            else
            {
                qDebug() << "getDroneSearches from getsearch error: "
                         << queryDrones.lastError();
            }*/
            //cant do due current state of model
        }

    }
    else
    {
       qDebug() << "addPerson error:  "
                << query.lastError();
    }
    return search;
}
