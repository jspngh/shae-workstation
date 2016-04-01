#ifndef DRONE_H
#define DRONE_H

#include <QString>
#include <QUuid>

/**
 * \brief The Drone class holds the data belonging to a drone.
 * The logic of a drone is implemented in the DroneModule class.
 * A DroneModule instance has a drone instance as member.
 */

class Drone
{

public:
    Drone();

    Drone(int dataPort, int streamPort, QString serverIp, QString streamPath , double visionWidth);

    Drone(QUuid droneID, int dataPort, int streamPort, QString serverIp, QString streamPath , double visionWidth);

    ~Drone();

    QUuid getGuid() const;

    int getPortNr();

    QString getServerIp();

    double getVisionWidth() const;

    void setVisionWidth(double visionWidth);

    int getStreamPortNr();

    QString getStreamPath() const;

    void setStreamPath(const QString &value);

private:
    QUuid guid; //!< The Global Unique Identifier that belongs to the drone.
    int dataPort; /*!< The port number that will be used to connect to the actual drone and send data */
    int streamPort;  /*!< The port number that will be used to start the stream on the drone */
    QString serverIp; /*!< The IP address of the actual drone, this will be 10.1.1.10 */
    QString streamPath;
    double visionWidth;

public:
    static constexpr double MIN_VISIONWIDTH = 0.00000001; //!< This is a lower bound to the visionwidth, since visionWidth cannot be zero.

};

#endif // DRONE_H
