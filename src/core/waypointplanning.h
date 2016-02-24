#ifndef WAYPOINTPLANNING_H
#define WAYPOINTPLANNING_H
#include <list>
#include "drone.h"

enum Direction{
    NORTH, SOUTH, EAST, WEST
};

//! Represents a coordinate, like used by the drone gps.
class Coordinate{
public:
    double latitude; //!< How much north or south
    double longitude;//!< How much east or west
    Coordinate(double la, double lo){
        latitude =la;
        longitude = lo;
    }
    static Coordinate goDirection(Coordinate start, Direction direction, double distance);
};

//! has something like coordinates that make a rectangle, or could be more advanced like a polygon defined by its corners.
class Area{


};

class RectangleArea: public Area{
public:
    Coordinate southWest;
    Coordinate northWest;
    Coordinate northEast;
    Coordinate southEast;
};

class PolygonArea: public Area{
public:
    std::list<Coordinate> cornersOfArea;
};




//! abstract class
class PathAlgorithm {

public:
    Coordinate start; //!< We will need this to efficiently divide search areas over the available drones, and to plan the beginning of the path as close to the start as possible.

    virtual std::list<Coordinate> calculateWaypoints(Area area, double visionWidth) = 0;
    void divideArea(Area area, std::list<Drone> drones);


};


//! A simple path algoritn
class SimplePathAlgorithm: public PathAlgorithm{
    public:
        std::list<Coordinate> calculateWaypoints(RectangleArea area, double visionWidth);
    private:
        double calculateDistance(Coordinate a, Coordinate b);
};




#endif // WAYPOINTPLANNING_H
