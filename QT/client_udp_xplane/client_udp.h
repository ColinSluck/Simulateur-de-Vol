#ifndef CLIENT_UDP_H
#define CLIENT_UDP_H

#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include <iostream>


#endif // CLIENT_UDP_H

class CclientUDPXplane
{
    private:
        int iResult = 0;
        WSADATA wsaData;
        struct sockaddr_in RecvAddr;
        unsigned short Port = 49001;
        char RecvBuf[41];
        int BufLen = 41;
        struct sockaddr_in SenderAddr;
        int SenderAddrSize = sizeof (SenderAddr);
    public:
        CclientUDPXplane();
        ~CclientUDPXplane();
};
