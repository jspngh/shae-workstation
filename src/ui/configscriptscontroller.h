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
    void connected_to_solo_network();
    void not_connected_to_solo_network(QString);
    void gateway_setted();
    void gateway_not_setted(QString);

public slots:
    void connect_to_solo_network();
    void set_gateway(QString ssid, QString password);
};

#endif // CONFIGSCRIPTSCONTROLLER_H
