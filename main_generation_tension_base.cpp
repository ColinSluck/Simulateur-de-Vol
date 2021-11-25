#include <QCoreApplication>
#include <stdio.h>
#include <NIDAQmx.h>
#include <QElapsedTimer>
#include <iostream>

#define NS 10


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TaskHandle taskhandle = nullptr;
    float valeur = 0;

    //int32 error;
    //Création de la tâche
    DAQmxCreateTask("task_roll",&taskhandle);
    // printf("erreur DAQmxCreateTask = %d\n", error);

    DAQmxCreateAOVoltageChan(taskhandle,"Dev6/ao0","Simulation",-10.0,10.0,DAQmx_Val_Volts,"");
    //printf("erreur DAQmxCreateAOVoltageChan  = %d\n", error);

    for(int i=0;i<3;i++)
    {
        printf("Entrez une valeur:\n");
        scanf("%d");
        DAQmxWriteAnalogScalarF64(taskhandle,1,10,valeur,NULL);
        //printf("DAQmxWriteAnalogScalarF64 = %d\n",error);
    }

    DAQmxStopTask(taskhandle);
    //printf("erreur DAQmxStopTask roll = %d\n", error);
    DAQmxClearTask(taskhandle);
    //printf("erreur DAQmxClearTask roll = %d\n", error);

    return a.exec();
}

