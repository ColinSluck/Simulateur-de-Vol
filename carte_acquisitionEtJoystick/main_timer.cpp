#include <QCoreApplication>
#include <stdio.h>
#include <NIDAQmx.h>
#include <chrono>
#include <thread>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TaskHandle taskhandle = nullptr;
    int32 error;

    //Initialisation de la valeur de la tension
    double tension = 10;
    double tension2 = -10;


    //Création de la tâche
    error = DAQmxCreateTask("Simulation",&taskhandle);
    printf("erreur DAQmxCreateTask roll = %d\n", error);

    //Création d'une sortie de voltage
    error = DAQmxCreateAOVoltageChan(taskhandle,"Dev6/ao0","Simulation",-10.0,10.0,DAQmx_Val_Volts,"");
    printf("erreur DAQmxCreateAOVoltageChan roll = %d\n", error);

    while (true)
    {
        //Permet d'écrire la valeur tension
        DAQmxWriteAnalogScalarF64(taskhandle,1,10,tension,NULL);
        //Timer en 1000 milliseconds = 1 seconde
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        //Permet d'écrire la valeur tension 2
        DAQmxWriteAnalogScalarF64(taskhandle,1,10,tension2,NULL);
        //Timer en 1000 milliseconds = 1 seconde
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    //Stop la tâche
    error = DAQmxStopTask(taskhandle);
    printf("erreur DAQmxStopTask roll = %d\n", error);

    //Efface la tâche
    error = DAQmxClearTask(taskhandle);
    printf("erreur DAQmxClearTask roll = %d\n", error);

    return a.exec();
}
