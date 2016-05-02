#ifndef CONFIGSCRIPTSCONTROLLER_H
#define CONFIGSCRIPTSCONTROLLER_H

#include <QObject>
#include <QProcess>
#include <QDebug>

class ConfigScriptsController : public QObject
{
    Q_OBJECT
public:
    explicit ConfigScriptsController(QObject *parent = 0);

signals:
    void connectedToSoloNetwork();
    void notConnectedToSoloNetwork(QString);
    void gatewaySetted();
    void gatewayNotSetted(QString);

public slots:
    void connectToSoloNetwork();
    void setGateway(QString ssid, QString password);
};

#endif // CONFIGSCRIPTSCONTROLLER_H
