#include "communication.h"
#include <QDebug>

Communication::Communication(QObject *parent):
    QObject(parent)
{
    qDebug() << "Communication created";
}

QString Communication::send()
{
    return QString("test");
}

