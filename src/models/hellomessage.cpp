#include "hellomessage.h"

HelloMessage(QString droneIp,
             QString streamFile,
             int commandsPort,
             int streamPort,
             double visionWidth):
    droneIp(droneIp),
    streamFile(streamFile),
    commandsPort(commandsPort),
    streamPort(streamPort),
    visionWidth(visionWidth)
{

}

HelloMessage::HelloMessage()
{

}

HelloMessage(const HelloMessage& hello)
{
    droneIp = hello.droneIp;
    streamFile = hello.streamFile;
    commandsPort = hello.commandsPort;
    streamPort = hello.streamPort;
    visionWidth = hello.visionWidth;
}

~HelloMessage()
{
    // nothing needs to be deleted
}

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

