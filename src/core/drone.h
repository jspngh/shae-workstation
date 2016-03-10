#ifndef DRONE_H
#define DRONE_H
#include <QGeoCoordinate>
#include <QString>
#include "communication.h"
#include <QJsonObject>
#include <QJsonDocument>

/*! \brief This is the class that represents a drone on the workstation.
 * This class can be used to send messages to the drone.

*/
class Drone
{
public:
    /*********
    Attributes
    **********/
    QString ID; //!< The ID of the drone.
    double visionWidth; //!< This attribute tells how wide the vision of the drone is. This is useful to calculate the waypoints. It should use the same scale as the coordinates used in the waypointplanning algorithms.
    std::list<QGeoCoordinate> waypoints; //!< Keeps the list of waypoints.
    Communication* communicationLink;

    /***********************
    Constructors/Destructors
    *************************/
    //! Empty constructor
    Drone();
    //! Constructor that sets the visionWidth of the drone
    Drone(double visionWidth);
    //! Destructor
    ~Drone();

    /***********************
    Control message methods
    ************************/
    //! Sends a Json message to the drone that contains all waypoints.
    void sendWaypoints();

    //! Sends a Json message to the drone to start the flight.
    void startFlight();

    //! Sends a Json message to the drone to stop the flight.
    void stopFlight();

    //! Sends a Json message to the drone to make an emergency landing.
    void emergencyLanding();





private:
    static const double MIN_VISIONWIDTH = 0.00000000001; //!< This is a lower bound to the visionwidth, since visionWidth cannot be zero.
};

#endif // DRONE_H
