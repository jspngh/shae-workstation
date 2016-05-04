#include "polygonpathalgorithm.h"

PolygonPathAlgorithm::PolygonPathAlgorithm()
    : PolygonPathAlgorithm(QGeoCoordinate(0.0, 0.0))
{
}

PolygonPathAlgorithm::PolygonPathAlgorithm(QGeoCoordinate start)
    : PathAlgorithm(start)
{
}

PolygonPathAlgorithm::PolygonPathAlgorithm(const PolygonPathAlgorithm &algo)
{
    this->start = algo.start;
}

PolygonPathAlgorithm::~PolygonPathAlgorithm()
{

}

QList<QGeoCoordinate> *PolygonPathAlgorithm::calculateWaypoints(QGeoRectangle area, double visionWidth)
{
    QList<QGeoCoordinate> coordinates = QList<QGeoCoordinate>();
    coordinates.push_back(area.bottomLeft());
    coordinates.push_back(area.bottomRight());
    coordinates.push_back(area.topLeft());
    coordinates.push_back(area.topRight());

    return calculateWaypoints(GeoPolygon(coordinates), visionWidth);
}

QList<QGeoCoordinate> *PolygonPathAlgorithm::calculateWaypoints(GeoPolygon area, double visionWidth)
{
    QList<QGeoCoordinate> *list = new QList<QGeoCoordinate>();

    //first go to closest of mostEast or mostWest
    double d1 = start.distanceTo(area.getMostEastCoordinate());
    double d2 = start.distanceTo(area.getMostWestCoordinate());
    Direction direction;
    double min = std::min(d1, d2);
    if (min == d1) {
        direction = WEST;
        list->push_back(area.getMostEastCoordinate());
    } else {
        direction = EAST;
        list->push_back(area.getMostWestCoordinate());
    }
    //qDebug() << list->back();

    //while going from wesst to East or vice versa (incrementing by visionWidth)
    do {


        //1. Take a step along the upperHull.
        auto pair = getNeighbouringEdges(list->back(), area.getUpperHull());
        list->push_back(PathAlgorithm::goDirectionBetween(list->back(), pair.first,
                        pair.second, visionWidth, direction));
        //qDebug() << list->back();
        if (list->back().longitude() >= area.getMostEastCoordinate().longitude()
                || list->back().longitude() <= area.getMostWestCoordinate().longitude())
            break;




        //2. Go South
        pair = getNeighbouringEdges(list->back(), area.getLowerHull());
        QGeoCoordinate south = PathAlgorithm::goDirectionBetween(pair.first, pair.first,
                               pair.second,
                               list->back().longitude() - pair.first.longitude(),
                               EAST);
        list->push_back(south);
        //qDebug() << list->back();




        //3. Take a step along the lowerHull
        pair = getNeighbouringEdges(list->back(), area.getLowerHull());
        list->push_back(PathAlgorithm::goDirectionBetween(list->back(), pair.first,
                        pair.second, visionWidth, direction));
        //qDebug() << list->back();
        if (list->back().longitude() >= area.getMostEastCoordinate().longitude()
                || list->back().longitude() <= area.getMostWestCoordinate().longitude())
            break;




        //4. Go North
        pair = getNeighbouringEdges(list->back(), area.getUpperHull());
        QGeoCoordinate north = PathAlgorithm::goDirectionBetween(pair.first, pair.first,
                               pair.second,
                               list->back().longitude() - pair.first.longitude(),
                               EAST);
        list->push_back(north);
        //qDebug() << list->back();



    } while (list->back().longitude() < area.getMostEastCoordinate().longitude()
             && list->back().longitude() > area.getMostWestCoordinate().longitude());

    //qDebug() << list->back().toString(QGeoCoordinate::DegreesMinutes);


    return list;
}

QPair<QGeoCoordinate, QGeoCoordinate> PolygonPathAlgorithm::getNeighbouringEdges(QGeoCoordinate from, QList<QGeoCoordinate> hull)
{
    QGeoCoordinate toTheWest, toTheEast;
    //go trough upperHull to get coordinate left from current latitude and right from current latitude.
    for (const QGeoCoordinate coordinate : hull) {
        if (coordinate.longitude() <= from.longitude())
            toTheWest = coordinate;
        if (!toTheEast.isValid() && coordinate.longitude() > from.longitude())
            toTheEast = coordinate;
    }
    if (!toTheEast.isValid())
        toTheEast = QGeoCoordinate(hull.back().latitude(), hull.back().longitude() + 0.0001);

    //qDebug() << "left: " << toTheWest << ", right: " << toTheEast;
    return QPair<QGeoCoordinate, QGeoCoordinate>(toTheWest, toTheEast);
}

void PolygonPathAlgorithm::setWaypointsForDrones(QGeoRectangle area, QList<DroneModule *> drones)
{
    QList<QGeoCoordinate> coordinates = QList<QGeoCoordinate>();
    coordinates.push_back(area.bottomLeft());
    coordinates.push_back(area.bottomRight());
    coordinates.push_back(area.topLeft());
    coordinates.push_back(area.topRight());
    setWaypointsForDrones(GeoPolygon(coordinates), drones);
}

void PolygonPathAlgorithm::setWaypointsForDrones(GeoPolygon area, QList<DroneModule *> drones)
{
    int numDrones = drones.size();

    double areaWidth = area.getMostEastCoordinate().longitude() - area.getMostWestCoordinate().longitude();
    double widthPerDrone = areaWidth / (double) numDrones;

    double border = area.getMostWestCoordinate().longitude() + widthPerDrone;
    QGeoCoordinate upperBorder = area.getMostWestCoordinate();
    QGeoCoordinate lowerBorder = area.getMostWestCoordinate();

    for (DroneModule *drone : drones) {
        QList<QGeoCoordinate> coordListPerDrone;

        if (!coordListPerDrone.contains(upperBorder))
            coordListPerDrone.push_back(upperBorder);
        if (!coordListPerDrone.contains(lowerBorder))
            coordListPerDrone.push_back(lowerBorder);

        for (QGeoCoordinate upper : area.getUpperHull()) {
            if (!coordListPerDrone.contains(upper) && upper.longitude() <= border && upper.longitude() >= (border - widthPerDrone))
                coordListPerDrone.push_back(upper);
        }
        for (QGeoCoordinate lower : area.getLowerHull()) {
            if (!coordListPerDrone.contains(lower) && lower.longitude() <= border && lower.longitude() >= (border - widthPerDrone))
                coordListPerDrone.push_back(lower);
        }
        auto upperPair = getNeighbouringEdges(QGeoCoordinate(0, border), area.getUpperHull());
        if (upperPair.second.longitude() <= area.getMostEastCoordinate().longitude()) {

            upperBorder = PathAlgorithm::goDirectionBetween(upperPair.first, upperPair.first,
                          upperPair.second,
                          border - upperPair.first.longitude(),
                          EAST);
        } else {
            upperBorder = area.getMostEastCoordinate();
        }

        if (!coordListPerDrone.contains(upperBorder))
            coordListPerDrone.push_back(upperBorder);

        auto lowerPair = getNeighbouringEdges(QGeoCoordinate(0, border), area.getLowerHull());
        if (lowerPair.second.longitude() <= area.getMostEastCoordinate().longitude()) {

            lowerBorder = PathAlgorithm::goDirectionBetween(lowerPair.first, lowerPair.first,
                          lowerPair.second,
                          border - lowerPair.first.longitude(),
                          EAST);
        } else {
            lowerBorder = area.getMostEastCoordinate();
        }

        if (!coordListPerDrone.contains(lowerBorder))
            coordListPerDrone.push_back(lowerBorder);

        double visionPerDrone = drone->getVisionWidth();
        drone->setWaypoints(calculateWaypoints(GeoPolygon(coordListPerDrone), visionPerDrone));
        border += widthPerDrone;
    }
}

