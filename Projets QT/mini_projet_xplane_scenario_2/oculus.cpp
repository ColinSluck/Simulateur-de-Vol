#include "oculus.h"
#define COLW setw(5)

Oculus::Oculus()
{
}

void Oculus::initialisation()
{
    // Initialize our session with the Oculus HMD.
    if (ovr_Initialize(nullptr) == ovrSuccess)
    {
        session = nullptr;
        result = ovr_Create(&session, &luid);
        if (result == ovrSuccess)
        {   // Then we're connected to an HMD!

            // Let's take a look at some orientation data.
            ovr_RecenterTrackingOrigin(session);
        }

    }
}

void Oculus::refreshData()
{
    ts = ovr_GetTrackingState(session, 0, true);

    tempHeadPose = ts.HeadPose;
    tempPose = tempHeadPose.ThePose;
    tempOrient = tempPose.Orientation;
    tempAV = ts.HeadPose.AngularVelocity;

    //rotation en quaternion 0.7 quand 90°
    angles[0] = (tempOrient.x*90)/0.7;
    angles[1] = (tempOrient.y*90)/0.7;
    angles[2] = (tempOrient.z*90)/0.7;

    vAngulaire[0] = tempAV.x;
    vAngulaire[1] = tempAV.y;
    vAngulaire[2] = tempAV.z;

    // Wait a bit to let us actually read stuff.
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Oculus::stop()
{
    ovr_Destroy(session);
    ovr_Shutdown();
    // If we've fallen through to this point, the HMD is no longer
    // connected.
}

void Oculus::printData()
{
    std::cout << std::fixed << std::setprecision(0) << "Orientation (pitch,yaw,roll,w):"
              << "\t" << angles[0] << "\370,"
              << "\t" << angles[1] << "\370,"
              << "\t" << angles[2] << "\370\t"
              << std::setprecision(2)
              <<"Vitesse Angulaire (pitch,yaw,roll):"
              << "\t" << vAngulaire[0] << "Rad/s,"
              << "\t" << vAngulaire[0] << "Rad/s,"
              << "\t" << vAngulaire[0] << "Rad/s" << std::endl;
}

float Oculus::getPitch() { return angles[0]; }

float Oculus::getPitchVitesse() { return vAngulaire[0]; }

float Oculus::getYaw() { return angles[1]; }

float Oculus::getYawVitesse() { return vAngulaire[1]; }

float Oculus::getRoll() { return angles[2]; }

float Oculus::getRollVitesse() { return vAngulaire[2]; }
