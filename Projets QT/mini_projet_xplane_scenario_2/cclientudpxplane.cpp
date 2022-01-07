#include "cclientudpxplane.h"

CclientUDPXplane::CclientUDPXplane() : BufLen(0)
{
    RecvAddr.sin_addr.s_addr = inet_addr("");
    RecvAddr.sin_port = htons(0);
    iResult = 0;
    roll = 0;
    pitch = 0;
}

CclientUDPXplane::~CclientUDPXplane()
{
    delete [] RecvBuf;
}

void CclientUDPXplane::configuration(const char* p_adresse,int p_port,int p_BufLen)
{
    RecvAddr.sin_addr.s_addr = inet_addr(p_adresse);
    RecvAddr.sin_port = htons(p_port);
    BufLen = p_BufLen;
}
void CclientUDPXplane::SocketON()
{
    //-----------------------------------------------
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup failed with error %d\n", iResult);
    }
    //-----------------------------------------------
    // Create a receiver socket to receive datagrams
    RecvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (RecvSocket == INVALID_SOCKET) {
        wprintf(L"socket failed with error %d\n", WSAGetLastError());
    }
    //-----------------------------------------------
    // Bind the socket to any address and the specified port.
    RecvAddr.sin_family = AF_INET;

    iResult = bind(RecvSocket, (SOCKADDR *) & RecvAddr, sizeof (RecvAddr));
    if (iResult != 0) {
        wprintf(L"bind failed with error %d\n", WSAGetLastError());
    }
}

void CclientUDPXplane::SocketOFF()
{
    //-----------------------------------------------
    // Close the socket when finished receiving datagrams
    wprintf(L"Finished receiving. Closing socket.\n");
    iResult = closesocket(RecvSocket);
    if (iResult == SOCKET_ERROR) {
        wprintf(L"closesocket failed with error %d\n", WSAGetLastError());
    }

    //-----------------------------------------------
    // Clean up and exit.
    wprintf(L"Exiting.\n");
    WSACleanup();
}

void CclientUDPXplane::RecieveData()
{
    //-----------------------------------------------
    // Call the recvfrom function to receive datagrams
    // on the bound socket.
    //wprintf(L"Receiving datagrams...\n");
    iResult = recvfrom(RecvSocket, RecvBuf, BufLen, 0, (SOCKADDR *) & SenderAddr, &SenderAddrSize);
    if (iResult == SOCKET_ERROR)
    {
        wprintf(L"recvfrom failed with error %d\n", WSAGetLastError());
    }
    pitch_IEEE = 0;
    roll_IEEE = 0;
    a = 3;
    x = 0;
    for(int i=16; i>12; i--)
    {
        roll_char[x] = RecvBuf[i];
        roll_IEEE += roll_char[x]<<(8*a);
        x++;
        a--;
    }
    a = 3;
    x = 0;
    for(int i=12; i>8; i--)
    {
        pitch_char[x] = RecvBuf[i];
        pitch_IEEE += pitch_char[x]<<(8*a);
        x++;
        a--;
    }
    roll = this->convertIEEEtoFloat(roll_IEEE);
    pitch = this->convertIEEEtoFloat(pitch_IEEE);

}

void CclientUDPXplane::printdata()
{

    printf("Roll reel : %.2f\tRoll volt : %.2f\t|\tPitch reel : %.2f\tPitch volt : %.2f\n",roll,getRollVolt(),pitch,getPitchVolt());
}

float CclientUDPXplane::convertIEEEtoFloat(int data_int)
{
    return *(float*)&data_int;
}

float CclientUDPXplane::getPitch() { return pitch; }

float CclientUDPXplane::getRoll() { return roll; }

float CclientUDPXplane::getRollVolt()
{
    if(-10<=roll && roll<=10)
    {
        return(roll*0.9);
    }
    else if(roll<-10)
    {
        return(-9);
    }
    else
    {
        return(9);
    }
}

float CclientUDPXplane::getPitchVolt()
{
    if(-10<=pitch && pitch<=10)
    {
        return(pitch * 0.9);
    }
    else if(pitch<-10)
    {
        return(-9);
    }
    else
    {
        return(9);
    }
}
