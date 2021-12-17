#include "cclientudpxplane.h"
#include "cusb_6xxx.h"
#include "bdd.h"
#include "oculus.h"
#include <QTimer>
int main()
{
    QTimer timer;
    timer.start();

    CUsb_6xxx *usb1=new CUsb_6xxx;
    usb1->configuration("Simulation","Dev6/ao0","ao0");
    usb1->configuration_2("Simulation2","Dev6/ao1","ao1");

    CclientUDPXplane *data=new CclientUDPXplane;
    data->configuration("127.0.0.1",49001,41);
    data->SocketON();

    Oculus dataOculus;
    dataOculus.initialisation();

    BDD *db=new BDD;
    db->initialisation();
    db->CLEAR();

    auto start = std::chrono::system_clock::now();
    while(true)
    {
        data->RecieveData();
        usb1->setAO0(-1 * data->getRollVolt());
        usb1->setAO1(data->getPitchVolt());
        data->printdata();

        dataOculus.refreshData();
        dataOculus.printData();

        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        db->Donnees(elapsed.count(),
                    data->getPitch(), data->getRoll(),
                    data->getPitchVolt(), data->getRollVolt(),
                    dataOculus.getRoll(), dataOculus.getPitch(), dataOculus.getYaw(),
                    dataOculus.getRollVitesse(), dataOculus.getPitchVitesse(), dataOculus.getYawVitesse());




    }
    data->SocketOFF();

    return 0;
}
