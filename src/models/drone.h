#ifndef DRONE_H
#define DRONE_H

#include <QString>
#include <QUuid>
#include <QMetaType>
#include <QDebug>

/**
 * \brief The Drone class holds the data belonging to a drone.
 * The logic of a drone is implemented in the DroneModule class.
 * A DroneModule instance has a drone instance as member.
 * \ingroup Models
 */
class Drone
{
public:
    /*!
     * \brief Drone default constructor
     * Creates a default Drone.
     */
    Drone();
    /*!
     * \brief Drone copy constructor
     */
    Drone(const Drone &d);
    /*!
     * \brief Drone destructor
     */
    ~Drone();
    /*!
     * \brief default Drone constructor
     * \param dronePort is the port to interface with the drone.
     * \param streamPort is the port to interface with the stream of the drone.
     * \param droneIp is ip to interface with the drone
     * \param controllerIp is ip to interface with the controller.
     * \param streamPath is configuration file of the drone stream
     * \param visionWidth is vision width of the drone
     */
    Drone(int dronePort, int streamPort, QString droneIp, QString controllerIp, QString streamPath , double visionWidth);
    /*!
     * \brief default Drone constructor
     * \param droneID is the id of the drone.
     * \param dronePort is the port to interface with the drone.
     * \param streamPort is the port to interface with the stream of the drone.
     * \param droneIp is the ip to interface with the drone
     * \param controllerIp is the ip to interface with the controller.
     * \param streamPath is the configuration file of the drone stream
     * \param visionWidth is the vision width of the drone
     */
    Drone(QUuid droneID, int dronePort, int streamPort, QString droneIp, QString controllerIp, QString streamPath , double visionWidth);

    /*!
     * \brief getGuid()
     * \return the Guid of the drone
     */
    QUuid getGuid();
    /*!
     * \brief getDronePort()
     * \return the port of the drone
     */
    int getDronePort();
    /*!
     * \brief getStreamPort()
     * \return the port of the stream
     */
    int getStreamPort();
    /*!
     * \brief getDroneIp()
     * \return the ip of the drone
     */
    QString getDroneIp();
    /*!
     * \brief getControllerIp()
     * \return the ip of the controller
     */
    QString getControllerIp();
    /*!
     * \brief getVisionWidth()
     * \return the vision width of the drone
     */
    double getVisionWidth() const;
    void setVisionWidth(double visionWidth);
    /*!
     * \brief getStreamPath()
     * \return the stream path
     */
    QString getStreamPath() const;
    void setStreamPath(const QString &value);

private:
    QUuid guid; //!< The Global Unique Identifier that belongs to the drone.
    int dronePort; /*!< The port number that will be used to connect to the actual drone and send data */
    int streamPort;  /*!< The port number that will be used to start the stream on the drone */
    QString droneIp; /*!< The IP address of the actual drone, this will be 10.1.1.10 */
    QString controllerIp; /*!< The IP address of the controller, this will be 10.1.1.1 */
    QString streamPath;
    double visionWidth; //!< double that says how wide the drone can see in decimal degrees longitude

public:
    static constexpr double MIN_VISIONWIDTH = 0.00000001; //!< This is a lower bound to the visionwidth, since visionWidth cannot be zero.

};

Q_DECLARE_METATYPE(Drone)

#endif // DRONE_H
