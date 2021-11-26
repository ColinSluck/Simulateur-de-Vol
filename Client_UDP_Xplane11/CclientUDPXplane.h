#ifndef CCLIENTUDPXPLANE_H
#define CCLIENTUDPXPLANE_H
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <QDebug>


class CclientUDPXplane
{
    private:
        int iResult;
        WSADATA wsaData;
        SOCKET RecvSocket;
        struct sockaddr_in RecvAddr;
        int BufLen;
        char* RecvBuf = new char[BufLen];
        struct sockaddr_in SenderAddr;
        int SenderAddrSize = sizeof (SenderAddr);
    public:
        CclientUDPXplane();
        ~CclientUDPXplane();
        void RecieveData();
        QString Convert(float &p_R);
        void SocketON();
        void SocketOFF();
        void configuration(const char*,int,int);
};

#endif // CCLIENTUDPXPLANE_H
