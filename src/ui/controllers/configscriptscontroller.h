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
    void connectToSoloNetwork();
    void setGateway(QString ssid, QString password);
};

#endif // CONFIGSCRIPTSCONTROLLER_H
