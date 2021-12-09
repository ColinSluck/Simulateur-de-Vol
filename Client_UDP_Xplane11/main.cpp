#include <QCoreApplication>
#include "CclientUDPXplane.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CclientUDPXplane data1;
    data1.configuration("127.0.0.1",49001,41);
    data1.SocketON();
    while(true)
    {
        data1.RecieveData();
        data1.printdata();
        data1.getRollVolt();
        data1.getPitchVolt();
        printf("pitch : %f\t\troll : %f", data1.getPitchVolt(), data1.getRollVolt());
    }
    data1.SocketOFF();

    return a.exec();
}
