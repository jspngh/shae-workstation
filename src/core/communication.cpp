#include "communication.h"

using namespace std;

Communication::Communication(string _hostIp, int _portNr)
    : hostIp(_hostIp.c_str()), portNr(_portNr)
{
}

int Communication::openConnection()
{
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("ERROR opening socket");
        // return error;
    }
    bzero((char *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(hostIp);
    serverAddress.sin_port = htons(portNr);
    return 0;
}

int Communication::sendData(string data, int len)
{
    if (connect(clientSocket,(struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        perror("ERROR connecting");
        // return error;
    }
    int n = write(clientSocket, data.c_str(), len);
    if (n < 0) {
         perror("ERROR writing to socket");
         // return error;
    }
    close(clientSocket);
    return 0;
}
