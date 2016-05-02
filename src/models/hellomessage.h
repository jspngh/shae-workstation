#ifndef HELLOMESSAGE_H
#define HELLOMESSAGE_H

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

/*!
 * \brief The HelloMessage class. A HelloMessage is exchanged between the drone and the workstation in order
 * to discover each other on the network. This allows a user to start the workstation/drone in different orders.
 * \ingroup Models
 */
class HelloMessage
{
public:
    /*!
     * \brief parse Creates a HelloMessage object from a Json hello messages that is send from the drone
     * \param helloRaw, raw bytes that have been received from a UDPsocket.
     * \return HelloMessage object with the datafields set according to the message
     */
    static HelloMessage parse(QByteArray helloRaw);

public:
    /*!
     * \brief HelloMessage default constructor
     * Creates a default HelloMessage object that initializes each of the different parameters.
     * \param droneIp, the ip to interface with the drone
     * \param streamPath, the configuration file of the drone stream
     * \param controllerIp, the ip to interface with the controller.
     * \param dronePort, the port to interface with the drone.
     * \param streamPort, the port to interface with the stream of the drone.
     * \param visionWidth, the vision width of the drone.
     */
    HelloMessage(QString droneIp,
                 QString streamPath,
                 QString controllerIp,
                 int dronePort,
                 int streamPort,
                 double visionWidth);

    HelloMessage();
    /*!
     * \brief HelloMessage copy constructor
     */
    HelloMessage(const HelloMessage &hello);
    /*!
     * \brief HelloMessage destructor
     */
    ~HelloMessage();

    double getVisionWidth() const;

    QString getStreamFile() const;

    QString getDroneIp() const;

    int getStreamPort() const;

    int getCommandsPort() const;

    QString getControllerIp() const;

private:
    double visionWidth = -1;
    QString streamFile;
    QString droneIp;
    QString controllerIp;
    int streamPort = -1;
    int commandsPort = -1;
};

#endif // HELLOMESSAGE_H
