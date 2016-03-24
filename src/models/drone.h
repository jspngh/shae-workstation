#ifndef DRONE_H
#define DRONE_H

#include <QObject>
#include <QString>
#include <QUuid>
#include <QGeoCoordinate>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "dronestatus.h"
#include "communication/droneheartbeatreceiver.h"

#include "communication/droneconnection.h"


class Controller;
class Search;

enum RequestedDroneStatus {
    Battery_Level, Location, Drone_Type, Waypoint_Reached, Next_Waypoint, Next_Waypoints, Speed, Selected_Speed, Height, Selected_Height, Camera_Angle, FPS, Resolution
};
enum RequestedDroneSetting {
    Height_To_Set, Speed_To_Set, Camera_Angle_To_Set, FPS_To_Set, Resolution_To_Set
};

/*! \brief This is the class that represents a drone on the workstation.
 * This class can be used to send messages to the drone.
 *  Note that each message methods sends a message, but returns a QJsondoc as well for testing and debugging purposes.

*/
class Drone : public QObject
{

    Q_OBJECT
public:
    /***********************
    Constructors/Destructor
    *************************/
    //! Default constructor

    //! This sets:
    //! visionwidth to MIN_VISIONWIDTH
    //! serverIp to 10.1.1.10
    //! portNr to 6330
    explicit Drone();

    //! Constructor that sets all important attributes of the drone object
    //! This is the constructor that should be used
    explicit Drone(int portNr, QString serverIp, double visionWidth = MIN_VISIONWIDTH);

    //! Copy constructor
    explicit Drone(const Drone &d);
    //! Destructor
    ~Drone();


    /***********************
    Getters/Setters
    ************************/
    void setController(Controller *ctrl);

    QUuid getGuid() const;

    int getPortNr();

    QString getServerIp();

    QList<QGeoCoordinate> *getWaypoints();

    void setWaypoints(QList<QGeoCoordinate> *waypoints);

    void addWaypoint(const QGeoCoordinate &waypoint);

    double getVisionWidth() const;

    void setVisionWidth(double visionWidth);

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
    //! Sends a Json messages to the drone that requests all statusses, possibly more than specified in the RequestedDroneStatus enum.
    QJsonDocument requestStatus();


    /*! \brief Sends a Json message to the drone to request a certain status.
     *  See RequestedDroneStatus enum to see which statuses can be requested.
     * This method actually uses the method to request multiple statuses, namely requestStatuses(). */
    QJsonDocument requestStatus(RequestedDroneStatus status);
    /*! \brief Sends a Json message to the drone to request certain multiple statuses.
     *  See RequestedDroneStatus enum to see which statuses can be requested. */
    QJsonDocument requestStatuses(QList<RequestedDroneStatus> statuses);
    //! Sends a Json message that asks for the heartbeat.
    QJsonDocument requestHeartbeat();

    /**************************
    Setting messages methods
    **************************/
    /*! \brief This method sends a message to let the drone know the workstation ip and port.
    */
    QJsonDocument setWorkstationConfiguration(QString ipAdress, int port);

    /*! \brief Sends a Json message to set a certain setting to a certain value.
     *  See RequestedDroneStatus enum to see which settings can be set.
     * This method actually uses the method to set mulitple settings, namely setSettings().
    */
    QJsonDocument setSetting(RequestedDroneSetting setting, int value);

    /*! \brief Sends a Json message to set certain settings to a certain values.
     * See RequestedDroneStatus enum to see which settings can be set.
    */
    QJsonDocument setSettings(QList<RequestedDroneSetting> settings, QList<int> values);


    /*******************
    Signals
    *******************/

signals:
    //! A signal generated to let droneconnection know that something needs to be sent.
    //! is connected to droneconnection directly in the constructor of drone.
    void droneRequest(QString message);

    //! A signal that is fired when a reply from a request is received and parsed to a DroneStatus object.
    //! Is connected to the mediator
    void droneStatusReceived(DroneStatus &status);

    //! A signal that is fired when a heartbeat is received and parsed to a DroneStatus object.
    //! Is connected to the mediator.
    void droneHeartBeatReceived(DroneStatus &status);

    /*********************
     Slots
     *********************/

private slots:
    //! Connected via mediator
    void onPathCalculated(Search *s);

    //! Connected directly with droneconnection.
    void onDroneResponse(const QString &response);
    //! Connected directly with droneconnection.
    void onDroneResponseError(int socketError, const QString &message);



private:
    /*********
    Attributes
    **********/

    Controller *controller;
    QUuid guid; //!< The Global Unique Identifier that belongs to the drone.

    DroneHeartBeatReceiver* heartbeatReceiver;

    QThread *connectionThread;
    DroneConnection *droneConnection;
    int portNr; /*!< The port number that will be used to connect to the actual drone */
    QString serverIp; /*!< The IP address of the actual drone, this will be 10.1.1.10 */

    QList<QGeoCoordinate> *waypoints; //!< Keeps the list of waypoints the drone needs to fly.

    //!< This attribute tells how wide the vision of the drone is.
    //!< This is useful to calculate the waypoints.
    //!< It should use the same scale as the coordinates used in the waypointplanning algorithms.
    double visionWidth;
    static constexpr double MIN_VISIONWIDTH = 0.00000000001; //!< This is a lower bound to the visionwidth, since visionWidth cannot be zero.

};

#endif // DRONE_H
