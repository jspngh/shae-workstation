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
}

QGeoCoordinate QMMarker::location() const
{
    Q_D(const QMMarker);
    return d->location;
}

void QMMarker::show()
{
    Q_D(QMMarker);
    d->evaluateMethod(QString("show()"));
}

void QMMarker::moveTo(const QGeoCoordinate &to)
{
    Q_D(QMMarker);
    d->evaluateMethod(QString("moveTo(%1, %2)")
        .arg(to.latitude()).arg(to.longitude())
    );
    d->location = to;
}

void QMMarker::rotate(const int degrees)
{
    Q_D(QMMarker);
    d->evaluateMethod(QString("rotate(%1)")
        .arg(degrees)
    );
}

void QMMarker::scale(const double width, const double height)
{
    Q_D(QMMarker);
    d->evaluateMethod(QString("scale(%1, %2)")
        .arg(width)
        .arg(height)
    );
}

void QMMarker::setIcon(const QString resource)
{
    Q_D(QMMarker);
    d->evaluateMethod(QString("setIcon(\"%1\")")
        .arg(resource)
    );
}

