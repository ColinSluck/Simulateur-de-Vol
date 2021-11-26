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

    error = DAQmxCreateTask("task_roll",&taskhandle_x);
    printf("erreur DAQmxCreateTask roll = %ld\n", error);
    error = DAQmxCreateTask("task_pitch",&taskhandle_y);
    printf("erreur DAQmxCreateTask pitch = %ld\n", error);

    error = DAQmxCreateAOVoltageChan(taskhandle_x,"Dev1/ao0","roll",-10,10,DAQmx_Val_Volts,"");
    printf("erreur DAQmxCreateAOVoltageChan roll = %ld\n", error);
    error = DAQmxCreateAOVoltageChan(taskhandle_y,"Dev1/ao1","pitch",-10,10,DAQmx_Val_Volts,"");
    printf("erreur DAQmxCreateAOVoltageChan pitch = %ld\n", error);

    while(true)
    {
        x = -1 * (sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::X)/10);
        y = sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::Y)/10;
        error = DAQmxWriteAnalogScalarF64 (taskhandle_x, 1, 10, x, NULL);
        error = DAQmxWriteAnalogScalarF64 (taskhandle_y, 1, 10, y, NULL);
        sf::Joystick::update();
    }

    error = DAQmxStopTask(taskhandle_x);
    printf("erreur DAQmxStopTask roll = %ld\n", error);
    error = DAQmxClearTask(taskhandle_x);
    printf("erreur DAQmxClearTask roll = %ld\n", error);
    error = DAQmxStopTask(taskhandle_y);
    printf("erreur DAQmxStopTask pitch = %ld\n", error);
    error = DAQmxClearTask(taskhandle_y);
    printf("erreur DAQmxClearTask pitch = %ld\n", error);

    return a.exec();


}

