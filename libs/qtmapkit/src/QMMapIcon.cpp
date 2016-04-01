#include "QMMapIcon.h"

QMMapIcon::QMMapIcon(QString resource, QObject *parent)
    : QObject(parent)
{
    this->resource = resource;

    setSize(30, 30);
    setOrigin(0, 0);
    setAnchor(0, 0);
}

QMMapIcon::~QMMapIcon()
{
}

void QMMapIcon::setSize(int width, int height)
{
    size.first = width;
    size.second = height;
}

void QMMapIcon::setOrigin(int x, int y)
{
    origin.first = x;
    origin.second = y;
}

void QMMapIcon::setAnchor(int x, int y)
{
    anchor.first = x;
    anchor.second = y;
}

QString QMMapIcon::toJsObject()
{
    QString format = QString("{ \
        url: \"%1\", \
        scaledSize: new google.maps.Size(%2,%3), \
        origin: new google.maps.Point(%4,%5), \
        anchor: new google.maps.Point(%6,%7) \
    }");

    return format
        .arg(resource)
        .arg(size.first).arg(size.second)
        .arg(origin.first).arg(origin.second)
        .arg(anchor.first).arg(anchor.second);
}

