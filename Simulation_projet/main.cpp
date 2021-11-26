#include <QCoreApplication>
#include <stdio.h>
#include <NIDAQmx.h>
#include <QElapsedTimer>
#include <chrono>
#include <thread>
#include <iostream>
#include <SFML/Window/Joystick.hpp>

#define NS 10


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TaskHandle taskhandle_x = nullptr;
    TaskHandle taskhandle_y = nullptr;
    int32 error;
    float x = 0;
    float y = 0;
    float Vmax = 5;
    sf::Joystick::update();
    //Création de la tâche X
    error = DAQmxCreateTask("task_roll",&taskhandle_x);
    printf("erreur DAQmxCreateTask roll = %d\n", error);
    //Création de la tâche Y
    error = DAQmxCreateTask("task_pitch",&taskhandle_y);
    printf("erreur DAQmxCreateTask pitch = %d\n", error);

    error = DAQmxCreateAOVoltageChan(taskhandle_x,"Dev6/ao1","roll",0.0,5.0,DAQmx_Val_Volts,"");
    printf("erreur DAQmxCreateAOVoltageChan roll = %d\n", error);
    error = DAQmxCreateAOVoltageChan(taskhandle_y,"Dev6/ao1","pitch",0.0,5.0,DAQmx_Val_Volts,"");
    printf("erreur DAQmxCreateAOVoltageChan pitch = %d\n", error);

    while(true)
    {
        x = (sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::X)+100) * (Vmax/200);
        y = (sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::Y)+100) * (Vmax/200);
        error = DAQmxWriteAnalogScalarF64 (taskhandle_x, 1, 10, x, NULL);
        error = DAQmxWriteAnalogScalarF64 (taskhandle_y, 1, 10, y, NULL);
        sf::Joystick::update();
    }

    error = DAQmxStopTask(taskhandle_x);
    printf("erreur DAQmxStopTask roll = %d\n", error);
    error = DAQmxClearTask(taskhandle_x);
    printf("erreur DAQmxClearTask roll = %d\n", error);
    error = DAQmxStopTask(taskhandle_y);
    printf("erreur DAQmxStopTask pitch = %d\n", error);
    error = DAQmxClearTask(taskhandle_y);
    printf("erreur DAQmxClearTask pitch = %d\n", error);

    return a.exec();
}

