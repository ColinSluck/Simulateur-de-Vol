#include "cclientudpxplane.h"
#include "cusb_6xxx.h"

int main()
{

    CUsb_6xxx *usb1=new CUsb_6xxx;
    usb1->configuration("Simulation","Dev6/ao0","ao0");
    usb1->configuration_2("Simulation2","Dev6/ao1","ao1");

    CclientUDPXplane *data=new CclientUDPXplane;
    data->configuration("127.0.0.1",49001,41);
    data->SocketON();

    while(true)
    {
        data->RecieveData();
        usb1->setAO0(-1 * data->getRollVolt());
        usb1->setAO1(data->getPitchVolt());
        data->printdata();
    }
    data->SocketOFF();

    return 0;
}
