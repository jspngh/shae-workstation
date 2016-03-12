#ifndef COMM_H
#define COMM_H

#include <QObject>

#include "droneconnection.h"

 class Communication : public QObject
 {
     Q_OBJECT

 public:


     /**
      * ... todo ...
      */
     Communication(QString serverIp, int portNr);

     ~Communication();
     /**
      * ... todo ...
      * returns 0 when everything is correct
      */
     int doRequest(const QString &message);

 private slots:
     void processResponse(const QString &response);
     void processError(int socketError, const QString &message);

 private:
     DroneConnection drone;
     const int portNr; /*!< The port number that will be used to connect to the drone */
     const QString serverIp; /*!< The IP address of the drone, this will be 10.1.1.10 */
 };

 #endif // COMM_H
