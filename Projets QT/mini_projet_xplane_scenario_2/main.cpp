#include "cclientudpxplane.h"
#include "cusb_6xxx.h"
#include "bdd.h"

int main()
{

    CUsb_6xxx *usb1=new CUsb_6xxx;
    BDD *db=new BDD;

    usb1->configuration("Simulation","Dev6/ao0","ao0");
    usb1->configuration_2("Simulation2","Dev6/ao1","ao1");
    CclientUDPXplane *data=new CclientUDPXplane;
    data->configuration("127.0.0.1",49001,41);
    data->SocketON();
    while(true)
    {
        data->RecieveData();
        usb1->setAO0(data->getRollVolt());
        usb1->setAO1(data->getPitchVolt());
        data->printdata();
        printf("pitch : %f\t\troll : %f", data->getPitchVolt(), data->getRollVolt());
        db->Donnees(data->getPitchVolt(),data->getRollVolt());
    }
    data->SocketOFF();

    return 0;
}
