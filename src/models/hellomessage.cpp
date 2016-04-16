#include "hellomessage.h"

HelloMessage::HelloMessage(QString droneIp,
                           QString streamFile,
                           QString controllerIp,
                           int commandsPort,
                           int streamPort,
                           double visionWidth):
    droneIp(droneIp),
    streamFile(streamFile),
    controllerIp(controllerIp),
    commandsPort(commandsPort),
    streamPort(streamPort),
    visionWidth(visionWidth)
{

}

HelloMessage::HelloMessage()
{

}

HelloMessage::HelloMessage(const HelloMessage &hello)
{
    droneIp = hello.droneIp;
    streamFile = hello.streamFile;
    controllerIp = hello.controllerIp;
    commandsPort = hello.commandsPort;
    streamPort = hello.streamPort;
    visionWidth = hello.visionWidth;
}

HelloMessage::~HelloMessage()
{
    // nothing needs to be deleted
}

// Static helper function to pare HelloMessages received over the network
HelloMessage HelloMessage::parse(QByteArray helloRaw)
{
    QJsonParseError err;
    QJsonDocument jsondoc = QJsonDocument::fromJson(helloRaw, &err);

    if (!jsondoc.isObject()) return HelloMessage();

    QJsonObject json = jsondoc.object();

    // read date fields
    QString ipDrone = json["ip_drone"].toString();
    int portCommands = json["port_commands"].toInt();
    int portStream = json["port_stream"].toInt();
    QString streamFile = json["stream_file"].toString();
    double visionWidth = json["vision_width"].toDouble();
    QString controllerIp = json["ip_controller"].toString();

    qDebug() << controllerIp;

    return HelloMessage(ipDrone, streamFile, controllerIp, portCommands, portStream, visionWidth);
}

// Getters

double HelloMessage::getVisionWidth() const
{
    return visionWidth;
}

QString HelloMessage::getStreamFile() const
{
    return streamFile;
}

QString HelloMessage::getDroneIp() const
{
    return droneIp;
}

int HelloMessage::getStreamPort() const
{
    return streamPort;
}

int HelloMessage::getCommandsPort() const
{
    return commandsPort;
}

QString HelloMessage::getControllerIp() const
{
    return controllerIp;
}

