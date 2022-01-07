#include "cclientudpxplane.h"
#include "cusb_6xxx.h"
#include "bdd.h"
#include "oculus.h"
#include <QTimer>
#include <QFile>
#include <QCoreApplication>

std::string* getConfig(char const*);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::string *line;
    line = getConfig("simulation.conf");

    std::string voie1 = line[0];
    std::string voie2 = line[1];
    std::string addresse_xplane = line[2];
    std::string port = line[3];

    std::cout << voie1 << std::endl
              << voie2 << std::endl
              << addresse_xplane << std::endl
              << port << std::endl;

    QTimer timer;
    timer.start();

    CUsb_6xxx *usb1=new CUsb_6xxx;
    usb1->configuration(QString::fromUtf8(line[0].c_str()));
    usb1->configuration_2(QString::fromUtf8(line[1].c_str()));

    CclientUDPXplane *data=new CclientUDPXplane;
    data->configuration(line[2].c_str(),std::stoi(line[3]),41);
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

    return a.exec();
}

std::string* getConfig(char const* fichier)
{
    QFile file(fichier);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QStringList dataFile = QString(file.readAll()).split("\n");
    static std::string line[4];
    QStringList buffer;
    for(int i = 0; i < 4; i++)
    {
        buffer = dataFile[i].split("=");
        line[i] = buffer[1].toStdString();
    }

    return line;
}

