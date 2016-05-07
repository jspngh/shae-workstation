#ifndef DRONEMODULE_H
#define DRONEMODULE_H

#include <QObject>
#include <QString>
#include <QUuid>
#include <QGeoCoordinate>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>


#include "models/dronestatus.h"
#include "communication/droneheartbeatreceiver.h"
#include "communication/droneconnection.h"
#include "communication/streamconnection.h"
#include "models/drone.h"
#include "videocontroller/videocontroller.h"

//forward declarations
class Search;
class Controller;
class DetectionController;
class PersistenceController;

/*!
 * \brief The RequestedDroneStatus enum is used to easily request a certain status from the drone.
 * \ingroup Communication
 */
enum RequestedDroneStatus {
    Battery_Level //!< the battery level
    , Location //!< the current location
    , Drone_Type//!< the type of the drone, e.g. 'Solo;
    , Waypoint_Order//!< the number of the waypoint last reached
    , Next_Waypoint//!< the coordidnates of the next waypoint
    , Next_Waypoints//!< the coordinates of all the folowing waypoints
    , Speed //!< the speed at which the drone is flying
    , Selected_Speed //!< the speed at which the drone should fly
    , Height //!<the current height of the drone
    , Selected_Height //!<the height the drone should fly
    , Camera_Angle //!< the angle of the camera, in degrees between 0 and 90
    , FPS //!< the fps that the drone is recording
    , Resolution //!< the resulution the drone is recording, specified by the height in pixels, e.g. 720
    , GPS_Count //!< the number of gps sattelites visible to the drone
};

/*!
 * \brief The RequestedDroneSetting enum is used to easily set a certain setting on the drone.
 * \ingroup Communication
 */
enum RequestedDroneSetting {
    Height_To_Set//!< used to specify the height in m that you want the drone to fly
    , Speed_To_Set //!< used to specify the speed in m/s you want the drone to fly
    , Camera_Angle_To_Set //!< used to specify the camera angle you want to set
    , FPS_To_Set //!< used to specify the fps at which the drone should recording, e.g. 30, 60, 90, 120.
    , Resolution_To_Set //!< used to specify the resulution in pixel height the drone should record, e.g. 720
};

/*! \brief DroneModule class contains a drone model and all the logic belonging to a drone.
 * The model (an instance of the class Drone) contains the data of a drone (ip, port, id, ...)
 * This class (DroneModule) adds the logic to this drone model.
 * \ingroup Communication
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
    //! droneIp to 10.1.1.10
    //! controllerIp to 10.1.1.1
    //! dronePort to 6330
    //! streamPort to 5502
    explicit DroneModule();

    /*! \brief Constructor that sets all important attributes of the drone object
    This is the constructor that should be used.
    \param dronePort is the port of the drone that can be used to connect to it.
    \param streamPort is the port of the workstation used for receiving the videostream.
    \param droneIP is the IPadress of the drone.
    \param controllerIP is the IPadress of the controller of the drone.
    \param workstationIP is the IPadress of the workstation.
    \param streamPath \TODO
    \param visionWidth is a double that describes how wide the drone can see in decimal degrees.
    \param video \TODO
    */
    explicit DroneModule(int dronePort,
                         int streamPort,
                         QString droneIp,
                         QString controllerIp,
                         QString workstationIp,
                         QString streamPath,
                         double visionWidth = MIN_VISIONWIDTH,
                         bool video = true);


    //! Copy constructor
    explicit DroneModule(const DroneModule &d);
    //! Destructor
    ~DroneModule();


    /***********************
    Getters/Setters
    ************************/
    void setMediator(Mediator *med);

    void getStreamConnection();
    void stopStreamConnection();

    PersistenceController *getPersistenceController() const;
    void setPersistenceController(PersistenceController *value);

    QUuid getGuid();

    int getDronePort();

    int getStreamPort();

    QString getDroneIp();

    QString getControllerIp();

    double getVisionWidth() const;

    void setVisionWidth(double visionWidth);

    Drone *getDrone();

    void setDrone(Drone *value);

    QList<QGeoCoordinate> *getWaypoints();

    void setWaypoints(QList<QGeoCoordinate> *waypoints);

    void addWaypoint(const QGeoCoordinate &waypoint);


    QGeoCoordinate getHomeLocation() const;


    DroneStatus getLastReceivedDroneStatus() const;

    VideoController *getVideoController() const;
    void setVideoController(VideoController *value);
    DetectionController *getDetectionController() const;
    DroneHeartBeatReceiver *getHeartbeatReceiver() const;
    DroneConnection *getDroneConnection() const;

    /***********************
    Navigation message methods
    ************************/
    //! Sends a Json message to the drone that contains all waypoints he has to fly (stored in attribute)
    //! \return QJsonDocument for debugging purposes
    QJsonDocument sendWaypoints();

    /**************************
    Setting messages methods
    **************************/
    /*! \brief This method sends a message to let the drone know the workstation ip and port.
     * \return QJsonDocument for debugging purposes
    */
    QJsonDocument setWorkstationConfiguration(QString ipAdress, int port);

    /*! \brief Sends a Json message to set a certain setting to a certain value.
     *  See RequestedDroneStatus enum to see which settings can be set.
     * This method actually uses the method to set multiple settings, namely setSettings().
     * \return QJsonDocument for debugging purposes
    */
    QJsonDocument setSetting(RequestedDroneSetting setting, int value);

    /*! \brief Sends a Json message to set certain settings to a certain values.
     * See RequestedDroneStatus enum to see which settings can be set.
     * \return QJsonDocument for debugging purposes
    */
    QJsonDocument setSettings(QList<RequestedDroneSetting> settings, QList<int> values);


    /*******************
    Signals
    *******************/


signals:
    //! \brief A signal generated to let droneconnection know that something needs to be sent.
    //! is connected to droneconnection directly in the constructor of drone.
    void droneRequest(QString message);

    //! \brief A signal generated to start the stream on the physical drone
    void streamRequest();

    //! \brief A signal that is fired when a reply from a request is received and parsed to a DroneStatus object.
    //! Is connected to the mediator
    void droneStatusReceived(DroneStatus *status);

    //!  \brief A signal that is fired when a heartbeat is received and parsed to a DroneStatus object.
    //! Is connected to the mediator.
    void droneHeartBeatReceived(DroneStatus *status);

    //!TODO: add comment
    void startStream(Drone *drone);

    //!TODO: add comment
    void stopStream(Drone *drone);

    //!TODO: add comment
    void startStreamWorkstation(DroneModule *dm);

    void landed(DroneModule *dm);

    /*********************
     Slots
     *********************/
public slots:
    //! \brief Sends a Json messages to the drone that requests all statusses,
    //!  possibly more than specified in the RequestedDroneStatus enum.
    //! \return QJSonDocument that is sent to the drone, for debugging purposes.
    QJsonDocument requestStatus();

    /*! \brief Sends a Json message to the drone to request a certain status.
     *  See RequestedDroneStatus enum to see which statuses can be requested.
     * This method actually uses the method to request multiple statuses, namely requestStatuses().
    \return QJSonDocument that is sent to the drone, for debugging purposes.*/
    QJsonDocument requestStatus(RequestedDroneStatus status);
    /*! \brief Sends a Json message to the drone to request certain multiple statuses.
     *  See RequestedDroneStatus enum to see which statuses can be requested.
    \return QJSonDocument that is sent to the drone, for debugging purposes.*/
    QJsonDocument requestStatuses(QList<RequestedDroneStatus> statuses);

    //! Sends a Json message that asks for the heartbeat.
    //! \return QJSonDocument that is sent to the drone, for debugging purposes.
    QJsonDocument requestHeartbeat();

    //! Allows to start the stream for a given drone, linked to a search and persistence component.
    void initStream();
    //! Allows to stop the stream for a given drone, linked to a search and persistence component.
    void stopStream();
    //! After buffering the stream for a while, the detection component can be started to analyse the footage.
    void initDetection();
    //! TODO: add comment
    void onSearchEmitted(Search *s);


    //! Sends a Json message to the drone to start the flight.
    //! \return QJSonDocument that is sent to the drone, for debugging purposes.
    QJsonDocument startFlight();

    //! Sends a Json message to the drone to stop the flight.
    //! \return QJSonDocument that is sent to the drone, for debugging purposes.
    QJsonDocument stopFlight();

    //! Sends a Json message to the drone to make an emergency landing.
    //! \return QJSonDocument that is sent to the drone, for debugging purposes.
    QJsonDocument emergencyLanding();

    //! Sends a Json message to the drone to return to home.
    //! \return QJSonDocument that is sent to the drone, for debugging purposes.
    QJsonDocument returnToHome();

private slots:
    //! Connected via mediator
    void onPathCalculated(Search *s);

    //! Connected directly with droneconnection.
    void onDroneResponse(const QString &response);
    //! Connected directly with droneconnection.
    void onDroneResponseError(int socketError, const QString &message);
    //! connected directly with
    void onDroneStatusReceived(DroneStatus *s);

private:
    void addSignalSlot(); //!< Helper function for connecting the slots and signals
    void initHeartbeat(); //!< Helper function to initialise the heartbeat connection

private:
    DroneStatus lastReceivedDroneStatus; //!< the last received DroneStatus object
    Drone *drone; //!< model containing the data of a drone that will be stored in the database
    Mediator *mediator; //!< a pointer to the mediator used for connecting the signals and the slots
    QString workstationIp; //!< the IP addres of the workstation
    QThread *videoThread; //!< a pointer to the videothread
    VideoController *videoController; //!< a pointer to the videocontroller
    DetectionController *detectionController; //!< a pointer to the detectionController
    PersistenceController *persistenceController; //!< a pointer to the persistenceController
    DroneHeartBeatReceiver *heartbeatReceiver = nullptr; //!< a pointer to the heartbeatReceiver
    Search* search; //!< a pointer to the search object this DroneModule object belongs to
    QThread *connectionThread; //!< a pointer to the connectionThread
    DroneConnection *droneConnection; //!< a pointer to the droneConnection object, used for receiving and sending messages to the drone.
    QThread *streamThread; //!< a pointer to the streamThread
    StreamConnection *streamConnection; //!< a pointer to the streamConnection, used to send the video data from drone to workstation.
    QList<QGeoCoordinate> *waypoints; //!< Keeps the list of waypoints the drone needs to fly.
    bool videoProcessing; //!< a bool that is true when the processing of the video is started.
    bool videoActive;
    bool videoInactive;
    bool isFlying;
    bool returningHome;
    double h0; //!< stores the altidude on which the drone was positioned when taking off
    QGeoCoordinate homeLocation; //!< The coordinate of the location the drone started its flight.
    static constexpr double MIN_VISIONWIDTH = 0.00000000001; //!< This is a lower bound to the visionwidth, since visionWidth cannot be zero.
};

#endif // DRONEMODULE_H
