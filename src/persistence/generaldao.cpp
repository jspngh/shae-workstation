#include "generaldao.h"

GeneralDAO::GeneralDAO()
{

}

QList<QGeoCoordinate> GeneralDAO::uncypherPathString(QString pathString)
{
    QList<QGeoCoordinate> returnList = QList<QGeoCoordinate>();
    QList<QString> coordinates = pathString.split(":");
    for(QString coordinate : coordinates){
        if(!coordinate.isEmpty())
        {
            QList<QString> coordinateValues = coordinate.split("-");
            returnList.append(QGeoCoordinate(coordinateValues.at(0).toDouble(),coordinateValues.at(1).toDouble()));
        }
    }
    return returnList;
}
