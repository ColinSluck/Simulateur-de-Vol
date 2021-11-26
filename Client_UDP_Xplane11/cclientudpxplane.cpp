#include "CclientUDPXplane.h"

CclientUDPXplane::CclientUDPXplane()
{
    RecvAddr.sin_addr.s_addr = inet_addr("");
    RecvAddr.sin_port = htons(0);
    iResult = 0;
    BufLen = 0;
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
    wprintf(L"Receiving datagrams...\n");
    iResult = recvfrom(RecvSocket, RecvBuf, BufLen, 0, (SOCKADDR *) & SenderAddr, &SenderAddrSize);
    if (iResult == SOCKET_ERROR)
    {
        wprintf(L"recvfrom failed with error %d\n", WSAGetLastError());
    }
    unsigned char pitch_char[4];
    int x = 0;
    for(int i=16; i>12; i--)
    {
        pitch_char[x] = RecvBuf[i];
        printf("%x ",pitch_char[x]);
        x++;
    }
    unsigned char roll_char[4];
    x = 0;
    for(int i=12; i>8; i--)
    {
        roll_char[x] = RecvBuf[i];
        printf("%x ",roll_char[x]);
        x++;
    }
}

QString CclientUDPXplane::Convert(float &p_R)
{
        unsigned char *p =(unsigned char *)&p_R;
        QString oct1;
        QString oct2;
        QString oct3;
        QString oct4;
        oct1.setNum(*p,16);
        oct2.setNum(*(p + 1), 16);
        oct3.setNum(*(p + 2), 16);
        oct4.setNum(*(p + 3), 16);
        QString stringResult = oct1 + " " + oct2 + " " + oct3 + " " + oct4;
        return(stringResult);
}
