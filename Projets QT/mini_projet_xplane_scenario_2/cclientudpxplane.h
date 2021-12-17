#ifndef CCLIENTUDPXPLANE_H
#define CCLIENTUDPXPLANE_H
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <QDebug>
#include <sstream>
#include <iomanip>



class CclientUDPXplane
{
    private:
        int iResult;
        WSADATA wsaData;
        SOCKET RecvSocket;
        struct sockaddr_in RecvAddr;
        int BufLen;
        int x;
        int a;
        char* RecvBuf = new char[BufLen];
        struct sockaddr_in SenderAddr;
        int SenderAddrSize = sizeof (SenderAddr);
        unsigned char pitch_char[4];
        unsigned char roll_char[4];
        int pitch_IEEE;
        int roll_IEEE;
        float roll;
        float pitch;
        float data_float;
    public:
        CclientUDPXplane();
        ~CclientUDPXplane();
        void RecieveData();
        void test();
        void SocketON();
        void SocketOFF();
        void configuration(const char*,int,int);
        void printdata();
        float convertIEEEtoFloat(int data_int);
        float getPitch();
        float getRoll();
        float getRollVolt();
        float getPitchVolt();
};

#endif // CCLIENTUDPXPLANE_H
