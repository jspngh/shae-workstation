#ifndef DRONEMODULE_H
#define DRONEMODULE_H

#include <QObject>
#include <QString>
#include <QUuid>
#include <QGeoCoordinate>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include "models/dronestatus.h"
#include "communication/droneheartbeatreceiver.h"
#include "communication/droneconnection.h"
#include "communication/streamconnection.h"
#include "models/drone.h"


class Controller;
class Search;

enum RequestedDroneStatus {
    Battery_Level, Location, Drone_Type, Waypoint_Reached, Next_Waypoint, Next_Waypoints, Speed, Selected_Speed, Height, Selected_Height, Camera_Angle, FPS, Resolution
};
enum RequestedDroneSetting {
    Height_To_Set, Speed_To_Set, Camera_Angle_To_Set, FPS_To_Set, Resolution_To_Set
};

/*! \brief DroneModule class contains a drone model and all the logic belonging to a drone.
 * The model (a instance of the class Drone) contains the data of a drone (ip, port, id, ...)
 * This class (DroneModule) is a add the logic to this drone model.
*/
class DroneModule : public QObject
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
    explicit DroneModule();

    //! Constructor that sets all important attributes of the drone object
    //! This is the constructor that should be used
    explicit DroneModule(int dataPort, int streamPort, QString serverIp, double visionWidth = MIN_VISIONWIDTH);

    //! Copy constructor
    explicit DroneModule(const DroneModule &d);
    //! Destructor
    ~DroneModule();


    /***********************
    Getters/Setters
    ************************/
    void setController(Controller *ctrl);

    void getStream();

    void stopStream();

    QUuid getGuid() const;

    int getPortNr();

    QString getServerIp();

    double getVisionWidth() const;

    void setVisionWidth(double visionWidth);

    Drone getDrone() const;

    void setDrone(const Drone &value);

    QList<QGeoCoordinate> *getWaypoints();

    void setWaypoints(QList<QGeoCoordinate> *waypoints);

    void addWaypoint(const QGeoCoordinate &waypoint);

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

    //! A signal generated to start the stream on the physical drone
    void streamRequest();

    //! A signal that is fired when a reply from a request is received and parsed to a DroneStatus object.
    //! Is connected to the mediator
    void droneStatusReceived(DroneStatus status);

    //! A signal that is fired when a heartbeat is received and parsed to a DroneStatus object.
    //! Is connected to the mediator.
    void droneHeartBeatReceived(DroneStatus status);

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
    Drone drone; //!< model containing the data of a drone that will be stored in the database

    Controller *controller;

    DroneHeartBeatReceiver *heartbeatReceiver;

    QThread *connectionThread;

    DroneConnection *droneConnection;

    QThread *streamThread;

    StreamConnection *streamConnection;

    QList<QGeoCoordinate> *waypoints; //!< Keeps the list of waypoints the drone needs to fly.

    static constexpr double MIN_VISIONWIDTH = 0.00000000001; //!< This is a lower bound to the visionwidth, since visionWidth cannot be zero.
};

#endif // DRONEMODULE_H
