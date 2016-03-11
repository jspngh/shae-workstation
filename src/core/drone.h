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

*/
class Drone
{
public:
    /*********
    Attributes
    **********/
    QString ID; //!< The ID of the drone.
    double visionWidth; //!< This attribute tells how wide the vision of the drone is. This is useful to calculate the waypoints. It should use the same scale as the coordinates used in the waypointplanning algorithms.
    std::list<QGeoCoordinate> waypoints; //!< Keeps the list of waypoints the drone needs to fly.
    Communication* communicationLink;

    /***********************
    Constructors/Destructors
    *************************/
    //! Empty constructor
    Drone();
    //! Constructor that sets the visionWidth of the drone
    Drone(double visionWidth);
    //! Constructor that sets the visionWidth of the drone
    Drone(Communication* commlink, double visionWidth);
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

    /**************************
    Status messages method
    **************************/
    /*! \brief Sends a Json message to the drone to request a certain status.
     *  See DroneStatus enum to see which statuses can be requested.
     * This method actually uses the method to request multiple statuses, namely requestStatuses(). */
    void requestStatus(DroneStatus status);
    /*! \brief Sends a Json message to the drone to request certain multiple statuses.
     *  See DroneStatus enum to see which statuses can be requested. */
    void requestStatuses(std::list<DroneStatus> statuses);
    //! Sends a Json message that asks for the heartbeat.
    void requestHeartbeat();

    /**************************
    Setting messages methods
    **************************/
    /*! \brief Sends a Json message to set a certain setting to a certain value.
     *  See DroneStatus enum to see which settings can be set.
     * This method actually uses the method to set mulitple settings, namely setSettings().
    */
    void setSetting(DroneSetting setting, int value);

    /*! \brief Sends a Json message to set certain settings to a certain values.
     * See Dronestatus enum to see which settings can be set.
    */
    void setSettings(std::list<DroneSetting> settings, std::List<int> values);





private:
    static const double MIN_VISIONWIDTH = 0.00000000001; //!< This is a lower bound to the visionwidth, since visionWidth cannot be zero.
};

#endif // DRONE_H
