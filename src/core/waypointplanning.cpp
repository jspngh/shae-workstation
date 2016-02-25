#include "waypointplanning.h"
#include <algorithm>
#include <list>

/*! \brief This function calculates the waypoints for a drone to cover an area.
 * This is done in a very simple way, just going north and south while incrementally going west or east.
*/
std::list<Coordinate> SimplePathAlgorithm::calculateWaypoints(RectangleArea area, double visionWidth){
    //create empty list of Coordinates that will contain the waypoints
    std::list<Coordinate> list = std::list<Coordinate>();

    //calculate distances from the start coordinate to each corner of the rectangular area
    double d1= calculateDistance(start, area.northEast);
    double d2= calculateDistance(start, area.northWest);
    double d3= calculateDistance(start, area.southEast);
    double d4= calculateDistance(start, area.southWest);

    //Set closest corner as first waypoint.
    double min = std::min(std::min(d1,d2),std::min(d3,d4));
    if(min == d1)
        list.push_back(area.northEast);
    else if(min == d2)
         list.push_back(area.northWest);
    else if(min == d3)
         list.push_back(area.southEast);
    else
        list.push_back(area.southWest);
    //go up until most north coordinate reached,
    list.push_back(Coordinate(area.northEast.latitude,list.back().longitude));

    //then try to go 1 step(=visionWidth) in direction (=first west). If going west exceeds the most western coordinate of the rectangle, set direction to east and go 1 step east.
    Direction direction = WEST;
    if (Coordinate::goDirection((list.back()), direction, visionWidth).longitude<area.northWest.longitude)
        direction =EAST;
    list.push_back(Coordinate::goDirection((list.back()), direction, visionWidth));

    //Go all the way south, until most south coordinate reached. Go 1 step in direction again.
    //Go north again, and so forth, until all area is covered.

    while(list.back().longitude < area.northEast.longitude && list.back().longitude > area.northWest.longitude ){
        //go South
        list.push_back(  Coordinate(area.southEast.latitude, list.back().longitude));
        //go direction
        list.push_back(Coordinate::goDirection((list.back()), direction, visionWidth));
        if(list.back().longitude < area.northEast.longitude && list.back().longitude > area.northWest.longitude ){
            //go north
            list.push_back(  Coordinate(area.northEast.latitude, list.back().longitude));
            //go direction
            list.push_back(Coordinate::goDirection((list.back()), direction, visionWidth));
        }
    }
    //Go South or North for the last time
    if(list.back().latitude == area.northEast.latitude)
        //Go south
        list.push_back(Coordinate(area.southEast.latitude, list.back().longitude));
    else
        //Go north
        list.push_back(Coordinate(area.northEast.latitude, list.back().longitude));



    //return list
    return list;
}

//!This function calculates the distance between two coordinates
double SimplePathAlgorithm::calculateDistance(Coordinate a, Coordinate b){
    double d1 = (a.latitude-b.latitude);
    double d2 = (a.longitude-b.longitude);
    return d1*d1+d2*d2;
}

Coordinate Coordinate::goDirection(Coordinate start, Direction direction, double distance){
    switch(direction){
    case NORTH:
        return   Coordinate(start.latitude+distance, start.longitude);
        break;
    case SOUTH:
        return   Coordinate(start.latitude-distance, start.longitude);
        break;
    case WEST:
        return   Coordinate(start.latitude, start.longitude-distance);
        break;
    case EAST:
        return   Coordinate(start.latitude, start.longitude+distance);
        break;
    default:
        return start ;
        break;
    }

}
