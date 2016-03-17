#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QString>

/*!
 * The Communication class...
 */
class Communication : public QObject
{
  public:
    explicit Communication(QObject *parent = 0);
    QString send();

};

#endif // COMMUNICATION_H

