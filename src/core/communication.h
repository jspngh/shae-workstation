#ifndef COMM_H
#define COMM_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

 /*!
 This is an example of a comment that doxygen will export. The Communication class...

 */
 class Communication
 {
     int clientSocket; /*!< The sock used to communicate, will be created when opening the connection */
     const int portNr; /*!< The port number that will be used to connect to the drone */
     const char* hostIp; /*!< The IP address of the drone, this will be 10.1.1.10 */
     struct sockaddr_in serverAddress; /*!< Detailed description after the member */
 public:
     /**
      * ... todo ...
      */
     Communication(std::string hostIp, int portNr);
     /**
      * ... todo ...
      * returns 0 when everything is correct
      */
     int openConnection();
     /**
      * ... todo ...
      * returns 0 when everything is correct
      */
     int sendData(std::string data, int len);

 };

 #endif // COMM_H
