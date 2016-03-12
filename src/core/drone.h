#ifndef DRONE_H
#define DRONE_H
#include <QGeoCoordinate>
#include <QString>
#include "communication.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QString>

enum DroneStatus
{
    Battery_Level, Location, Drone_Type, Waypoint_Reached
};
enum DroneSetting
{
    Height, Speed, Camera_Angle, FPS, Resolution
};

/*! \brief This is the class that represents a drone on the workstation.
 * This class can be used to send messages to the drone.
 *  Note that each message methods sends a message, but returns a QJsondoc as well for testing and debugging purposes.

*/
class Drone
{
public:
    /*********
    Attributes
    **********/
    //QString ID; //!< The ID of the drone.
    double visionWidth; //!< This attribute tells how wide the vision of the drone is. This is useful to calculate the waypoints. It should use the same scale as the coordinates used in the waypointplanning algorithms.
    std::list<QGeoCoordinate> waypoints; //!< Keeps the list of waypoints the drone needs to fly.
    Communication* communicationLink;

    /***********************
    Constructors/Destructors
    *************************/
    //! Empty constructor that sets visionwidth = 0.000001.
    Drone();
    //! Constructor that sets the visionWidth of the drone.
    Drone(double visionWidth);
    //! Constructor that sets the visionWidth of the drone and the Communication object
    Drone(Communication* commlink, double visionWidth);
    //! Destructor
    ~Drone();

    /***********************
    Navigation message methods
    ************************/
    //! Sends a Json message to the drone that contains all waypoints.
    QJsonDocument sendWaypoints();

    //! Sends a Json message to the drone to start the flight.
    QJsonDocument startFlight();

    //! Sends a Json message to the drone to stop the flight.
    QJsonDocument stopFlight();

    //! Sends a Json message to the drone to make an emergency landing.
    QJsonDocument emergencyLanding();

    /**************************
    Status messages method
    **************************/
    /*! \brief Sends a Json message to the drone to request a certain status.
     *  See DroneStatus enum to see which statuses can be requested.
     * This method actually uses the method to request multiple statuses, namely requestStatuses(). */
    QJsonDocument requestStatus(DroneStatus status);
    /*! \brief Sends a Json message to the drone to request certain multiple statuses.
     *  See DroneStatus enum to see which statuses can be requested. */
    QJsonDocument requestStatuses(std::list<DroneStatus> statuses);
    //! Sends a Json message that asks for the heartbeat.
    QJsonDocument requestHeartbeat();

    /**************************
    Setting messages methods
    **************************/
    /*! \brief Sends a Json message to set a certain setting to a certain value.
     *  See DroneStatus enum to see which settings can be set.
     * This method actually uses the method to set mulitple settings, namely setSettings().
    */
    QJsonDocument setSetting(DroneSetting setting, int value);

    /*! \brief Sends a Json message to set certain settings to a certain values.
     * See Dronestatus enum to see which settings can be set.
    */
    QJsonDocument setSettings(std::list<DroneSetting> settings, std::list<int> values);





private:
    static const double MIN_VISIONWIDTH = 0.00000000001; //!< This is a lower bound to the visionwidth, since visionWidth cannot be zero.
};

#endif // DRONE_H
