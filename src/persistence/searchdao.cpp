#include "searchdao.h"
#include <QDebug>
#include <QGeoRectangle>
#include <GeoPolygon.h>

SearchDAO::SearchDAO()
{
}

SearchDAO::SearchDAO(QSqlDatabase *projectShaeDatabase)
{
    this->projectShaeDatabase = projectShaeDatabase;
}

Search* SearchDAO::dbSaveSearch(Search *search)
{
    QSqlQuery query;
    query.prepare("INSERT INTO searches (searchID, startTime, area, height, gimballAngle, fpsProcessing) "
                  "VALUES (:searchID, :startTime, :area, :height, :gimballAngle, :fpsProcessing)");

    QString pathString;

    if(search->getArea()->type() == QGeoShape::RectangleType) {
        QGeoRectangle* area = static_cast<QGeoRectangle*>(search->getArea());
        QString format = QString("%1-%2:%3-%4:");
        pathString = format.arg(area->topLeft().latitude())
                           .arg(area->topLeft().longitude())
                           .arg(area->bottomRight().latitude())
                           .arg(area->bottomRight().longitude());
    } else {
        GeoPolygon* area = static_cast<GeoPolygon*>(search->getArea());
        //TODO
    }

    query.bindValue(":searchID", search->getSearchID());
    query.bindValue(":startTime", search->getStartTime());
    query.bindValue(":area", pathString);
    query.bindValue(":height", search->getHeight());
    query.bindValue(":gimballAngle", search->getGimbalAngle());
    query.bindValue(":fpsProcessing", search->getFpsProcessing());
    if (query.exec()) {
    } else {
        qDebug() << "addsearch error:  "
                 << query.lastError();
    }
    return search;
}

Search* SearchDAO::dbRetrieveSearch(QUuid searchId)
{
    QSqlQuery query;
    Search *search;
    query.prepare("SELECT * FROM searches WHERE searchID = (:searchID)");
    query.bindValue(":searchID", searchId);
    if (query.exec()) {
        if (query.next()) {
            QList<QGeoCoordinate> coordinates = *uncypherPathString(query.value(2).toString());
            QGeoRectangle* area = new QGeoRectangle(coordinates.at(0), coordinates.at(1));
            search = new Search(searchId, query.value(1).toTime(), area,
                            query.value(3).toInt(), query.value(4).toInt(), query.value(5).toInt());
        }

    } else {
        qDebug() << "addPerson error:  "
                 << query.lastError();
    }
    return search;
}

