#include <QCoreApplication>
#include "CclientUDPXplane.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CclientUDPXplane data1;
    data1.configuration("127.0.0.1",49001,41);
    data1.SocketON();
    data1.RecieveData();
    data1.SocketOFF();

    return a.exec();
}
