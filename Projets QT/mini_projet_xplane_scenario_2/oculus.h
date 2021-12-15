#ifndef OCULUS_H
#define OCULUS_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <iomanip>
#include <OVR_CAPI.h>
#include <thread>

class Oculus
{
private:
    ovrSession session;
    ovrGraphicsLuid luid;
    ovrResult result;
    ovrTrackingState ts;
    ovrPoseStatef tempHeadPose;
    ovrPosef tempPose;
    ovrQuatf tempOrient;
    ovrVector3f tempAV;

    // (x, y, z) => (pitch, yaw, roll)
    float angles[3];        //tableau des angles sur x, y, z du casque VR en °
    float vAngulaire[3];    //tableau de la vitesse angulaire sur x, y, z du casque VR en rad/s

public:
    Oculus();
    void initialisation(); //Creer une session vr si le casque est connecté
    void refreshData(); //refraichi les données d'angles
    void stop(); //ferme la session
    void printData(); //affiche la valeurs des angles et de leurs vitesse dans la console

    float getPitch();
    float getPitchVitesse();
    float getYaw();
    float getYawVitesse();
    float getRoll();
    float getRollVitesse();
};

#endif // OCULUS_H
