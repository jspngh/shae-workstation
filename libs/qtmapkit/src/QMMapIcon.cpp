#include "QMMapIcon.h"

QMMapIcon::QMMapIcon(const QString resource, QObject *parent)
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

void QMMapIcon::setSize(const int width, const int height)
{
    size = QSize(width, height);
}

void QMMapIcon::setOrigin(const int x, const int y)
{
    origin = QPoint(x, y);
}

void QMMapIcon::setAnchor(const int x, const int y)
{
    anchor = QPoint(x, y);
}

QString QMMapIcon::toJsObject() const
{
    QString format = QString("{ \
        url: \"%1\", \
        scaledSize: new google.maps.Size(%2,%3), \
        origin: new google.maps.Point(%4,%5), \
        anchor: new google.maps.Point(%6,%7) \
    }");

    return format
        .arg(resource)
        .arg(size.width()).arg(size.height())
        .arg(origin.x()).arg(origin.y())
        .arg(anchor.x()).arg(anchor.y());
}

