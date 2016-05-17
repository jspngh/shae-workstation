#ifndef CONFIGSCRIPTSCONTROLLER_H
#define CONFIGSCRIPTSCONTROLLER_H

#include <QObject>
#include <QProcess>
#include <QFile>
#include <QStandardPaths>
#include <QDebug>
#include <QDir>

/*!
 * \brief The ConfigScriptsController class controls the configuration scripts for e.g. setting the gateway of the controller
 * \ingroup Controllers
 The ConfigScriptsController class controls two configuration scripts. The first one connects the workstation to the solo wireless network.
 The second one asks for a network name and password and uses these two to set a gateway to the solo wireless network.
 When a gateway is set, every device on the solo wireless network has access to the internet.
 Both scripts are bash script and are loaded into the resources. From there on, they are callable via their own slot, implemented in this class.
 */
class ConfigScriptsController : public QObject
{
    Q_OBJECT
public:
    explicit ConfigScriptsController(QObject *parent = 0);
private:
    QString standardDataFolder();
signals:
    void connectedToSoloNetwork();
    void notConnectedToSoloNetwork(QString);
    void gatewaySet();
    void gatewayNotSet(QString);

public slots:
    //! Calls the bash script that connects the workstation to the solo wireless network
    //! Emits the signal connectedToSoloNetwork() if the connection was successful
    //! Emits the signal notConnectedToSoloNetwork(QString) if the connection was unsuccessful
    void connectToSoloNetwork();

    //! Calls the bash script that sets a gateway on the solo wireless network
    //! Two parameters are required: ssid and password.
    //! ssid is the network name, password is the password for the network with the corresponding ssid
    //! Emits the signal gatewaySet() if the gateway was set successful
    //! Emits the signal gatewayNotSet(QString) if the gateway was no set successful
    void setGateway(QString ssid, QString password);
};

#endif // CONFIGSCRIPTSCONTROLLER_H
