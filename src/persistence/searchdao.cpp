#include "searchdao.h"
#include <QDebug>
#include <sstream>
#include <string>
#include <iostream>


SearchDAO::SearchDAO()
{
}

SearchDAO::SearchDAO(QSqlDatabase *projectShaeDatabase)
{
    this->projectShaeDatabase = projectShaeDatabase;
}

Search SearchDAO::dbSaveSearch(Search search)
{
    QSqlQuery query;
    query.prepare("INSERT INTO searches (searchID, startTime, area, height, gimballAngle, fpsProcessing) "
                  "VALUES (:searchID, :startTime, :area, :height, :gimballAngle, :fpsProcessing)");

    std::ostringstream os;

    os << search.getArea().topLeft().latitude() << "-" << search.getArea().topLeft().longitude() << ":";
    os << search.getArea().bottomRight().latitude() << "-" << search.getArea().bottomRight().longitude() << ":";

    QString pathString = QString(os.str().c_str());

    query.bindValue(":searchID", search.getSearchID());
    query.bindValue(":startTime", search.getStartTime());
    query.bindValue(":area", pathString);
    query.bindValue(":height", search.getHeight());
    query.bindValue(":gimballAngle", search.getGimbalAngle());
    query.bindValue(":fpsProcessing", search.getFpsProcessing());
    if (query.exec()) {
    } else {
        qDebug() << "addsearch error:  "
                 << query.lastError();
    }
    return search;
}

Search SearchDAO::dbRetrieveSearch(QUuid searchId)
{
    QSqlQuery query;
    Search search;
    query.prepare("SELECT * FROM searches WHERE searchID = (:searchID)");
    query.bindValue(":searchID", searchId);
    if (query.exec()) {
        if (query.next()) {
            QList<QGeoCoordinate> coordinates = uncypherPathString(query.value(2).toString());
            QGeoRectangle area = QGeoRectangle(coordinates.at(0), coordinates.at(1));
            search = Search(searchId, query.value(1).toTime(), area,
                            query.value(3).toInt(), query.value(4).toInt(), query.value(5).toInt());
        }

    } else {
        qDebug() << "addPerson error:  "
                 << query.lastError();
    }
    return search;
}
