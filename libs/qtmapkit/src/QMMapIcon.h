#ifndef QMMAPICON_H
#define QMMAPICON_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QString>

/*!
 * \note (0,0) is topleft of the icon.
 */
class QMMapIcon : public QObject
{
    Q_OBJECT

private:
    QString resource;
    QSize size;
    QPoint origin;
    QPoint anchor;

public:
    QMMapIcon(const QString resource, QObject *parent = 0);
    ~QMMapIcon();

    void setSize(const int width, const int height);
    void setOrigin(const int x, const int y);
    void setAnchor(const int x, const int y);

    QString toJsObject() const;
};

#endif // QMMAPICON_H

