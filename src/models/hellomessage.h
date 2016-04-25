#ifndef HELLOMESSAGE_H
#define HELLOMESSAGE_H

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

/*!
 * \brief The HelloMessage class
 * \ingroup Models
 */
class HelloMessage
{
public:
    /**
     * @brief parse Creates a HelloMessage object from a Json hello messages that is send from the drone
     * @param helloRaw
     * @return HelloMessage object with the datafields set according to the message
     */
    static HelloMessage parse(QByteArray helloRaw);

public:
    HelloMessage(QString droneIp,
                 QString streamFile,
                 QString controllerIp,
                 int commandsPort,
                 int streamPort,
                 double visionWidth);

    HelloMessage();
    HelloMessage(const HelloMessage &hello);
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
