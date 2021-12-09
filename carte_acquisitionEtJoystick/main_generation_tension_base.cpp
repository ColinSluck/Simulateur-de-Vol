#include <QCoreApplication>
#include <stdio.h>
#include <NIDAQmx.h>
#include <QElapsedTimer>
#include <iostream>
#include "cusb_6xxx.h"
#include "cusb_6xxx.cpp"

#define NS 10


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CUsb_6xxx *usb1=new CUsb_6xxx;
    usb1->configuration("Simulation","Dev6","ao0");
    usb1->setAO0(5.5);

    CUsb_6xxx *usb2=new CUsb_6xxx;
    usb2->configuration_2("Simulation2","Dev6","ao1");
    usb2->setAO1(-7.5);



    return a.exec();
}

