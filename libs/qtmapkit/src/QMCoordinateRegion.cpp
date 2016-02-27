/*****************************************************************************
 * QMCoordinateRegion.cpp
 *
 * Created: 08/7 2013 by uranusjr
 *
 * Copyright 2013 uranusjr. All rights reserved.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 *****************************************************************************/

#include "QMCoordinateRegion.h"
#include <QtDebug>

QMCoordinateRegion::QMCoordinateRegion() :
    _east(0.0), _west(0.0), _north(0.0), _south(0.0)
{
}

QMCoordinateRegion::QMCoordinateRegion(QGeoCoordinate southWest,
                                       QGeoCoordinate northEast) :
    _east(northEast.longitude()),
    _west(southWest.longitude()),
    _north(northEast.latitude()),
    _south(southWest.latitude())
{
}

QMCoordinateRegion::QMCoordinateRegion(qreal north, qreal south,
                                       qreal east, qreal west) :
    _east(east), _west(west), _north(north), _south(south)
{
}

bool QMCoordinateRegion::contains(QGeoCoordinate &point, bool proper) const
{
    qreal lng = point.longitude();
    qreal lat = point.latitude();

    bool r = false;
    if (proper)
        r = lat > west() && lat < east() && lng > south() && lng < north();
    else
        r = lat >= west() && lat <= east() && lng >= south() && lng <= north();

    return r;
}

bool QMCoordinateRegion::isEmpty() const
{
    return (east() == west()) || (north() == south());
}

qreal QMCoordinateRegion::east() const
{
    return _east;
}

qreal QMCoordinateRegion::west() const
{
    return _west;
}

qreal QMCoordinateRegion::north() const
{
    return _north;
}

qreal QMCoordinateRegion::south() const
{
    return _south;
}

void QMCoordinateRegion::setEast(qreal value)
{
    _east = value;
}

void QMCoordinateRegion::setWest(qreal value)
{
    _west = value;
}

void QMCoordinateRegion::setNorth(qreal value)
{
    _north = value;
}

void QMCoordinateRegion::setSouth(qreal value)
{
    _south = value;
}

QGeoCoordinate QMCoordinateRegion::southWest() const
{
    return QGeoCoordinate(south(), west());
}

QGeoCoordinate QMCoordinateRegion::northEast() const
{
    return QGeoCoordinate(north(), east());
}

QGeoCoordinate QMCoordinateRegion::southEast() const
{
    return QGeoCoordinate(south(), east());
}

QGeoCoordinate QMCoordinateRegion::northWest() const
{
    return QGeoCoordinate(north(), west());
}

QGeoCoordinate QMCoordinateRegion::center() const
{
    return QGeoCoordinate((north() + south()) / 2, (east() + west()) / 2);
}

bool QMCoordinateRegion::operator ==(const QMCoordinateRegion &other)
{
    return (east() == other.east())
            && (west() == other.west())
            && (north() == other.north())
            && (south() == other.south());
}
