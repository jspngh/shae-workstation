#include "QMMarker.h"

class QMMarkerPrivate
{
    Q_DECLARE_PUBLIC(QMMarker)

public:
    QMMarkerPrivate(QMMarker *q)
        : q_ptr(q)
    {
    }
    ~QMMarkerPrivate() {}
    QMMarker *q_ptr;

    QWebFrame *frame;
    QString id;
    QGeoCoordinate location;
    double orientation;

    inline QVariant evaluateMethod(const QString &eval)
    {
        QString script = QString("mapKit.getMarker(\"%1\").%2;")
                         .arg(id).arg(eval);
        return frame->evaluateJavaScript(script);
    }
};

QMMarker::QMMarker(QString id, const QGeoCoordinate &location, QWebFrame *frame, QObject *parent) :
    QObject(parent),
    d_ptr(new QMMarkerPrivate(this))
{
    Q_D(QMMarker);
    d->frame = frame;
    d->id = id;
    d->location = location;
    d->orientation = 0;
}

QGeoCoordinate QMMarker::location() const
{
    Q_D(const QMMarker);
    return d->location;
}

double QMMarker::orientation() const
{
    Q_D(const QMMarker);
    return d->orientation;
}

void QMMarker::show()
{
    Q_D(QMMarker);
    d->evaluateMethod(QString("show()"));
}

void QMMarker::trackPath()
{
    Q_D(QMMarker);
    d->evaluateMethod(QString("trackPath()"));
}

void QMMarker::moveTo(const QGeoCoordinate &to)
{
    Q_D(QMMarker);
    d->evaluateMethod(QString("moveTo(%1, %2)")
                      .arg(to.latitude()).arg(to.longitude())
                     );
    d->location = to;
}

void QMMarker::rotate(const double degrees)
{
    Q_D(QMMarker);
    d->evaluateMethod(QString("rotate(%1)").arg(degrees));
    d->orientation += degrees;
}

void QMMarker::setOrientation(const double degrees)
{
    Q_D(QMMarker);
    if (degrees == d->orientation) return;

    rotate(degrees - d->orientation);
}

void QMMarker::scale(const double width, const double height)
{
    Q_D(QMMarker);
    d->evaluateMethod(QString("scale(%1, %2)")
                      .arg(width)
                      .arg(height)
                     );
}

void QMMarker::setOpacity(const double alpha)
{
    Q_D(QMMarker);
    QString format = QString("setOpacity(%1)");
    QString js = format.arg(alpha);
    d->evaluateMethod(js);
}

void QMMarker::setIcon(const QString resource)
{
    Q_D(QMMarker);
    d->evaluateMethod(QString("setIcon(\"%1\")")
                      .arg(resource)
                     );
    d->orientation = 0;
}

