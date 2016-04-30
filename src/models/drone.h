#ifndef DRONE_H
#define DRONE_H

#include <QString>
#include <QUuid>
#include <QMetaType>

/**
 * \brief The Drone class holds the data belonging to a drone.
 * The logic of a drone is implemented in the DroneModule class.
 * A DroneModule instance has a drone instance as member.
 * \ingroup Models
 */
class Drone
{
public:
    //! default constructor that sets everything to a certain default value
    Drone();

    //! Copy constructor
    Drone(const Drone &d);
    //! destructor
    ~Drone();

    //! Constructor given all arguments, generates a unique QUuid
    Drone(int dronePort, int streamPort, QString droneIp, QString controllerIp, QString streamPath , double visionWidth);

    //! Constructor to set QUuid en everything else manually
    Drone(QUuid droneID, int dronePort, int streamPort, QString droneIp, QString controllerIp, QString streamPath , double visionWidth);

    QUuid getGuid() const;

    int getDronePort();

    int getStreamPort();

    QString getDroneIp();

    QString getControllerIp();

    double getVisionWidth() const;

    void setVisionWidth(double visionWidth);

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
