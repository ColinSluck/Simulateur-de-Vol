#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <iomanip>
#include <OVR_CAPI.h>
#include <thread>

#define COLW setw(15)

using namespace std;

int main()
{

    // Initialize our session with the Oculus HMD.
    if (ovr_Initialize(nullptr) == ovrSuccess)
    {
        ovrSession session = nullptr;
        ovrGraphicsLuid luid;
        ovrResult result = ovr_Create(&session, &luid);

        if (result == ovrSuccess)
        {   // Then we're connected to an HMD!

            // Let's take a look at some orientation data.
            ovrTrackingState ts;
            ovr_RecenterTrackingOrigin(session);
            while (true)
            {

                ts = ovr_GetTrackingState(session, 0, true);

                ovrPoseStatef tempHeadPose = ts.HeadPose;
                ovrPosef tempPose = tempHeadPose.ThePose;
                ovrQuatf tempOrient = tempPose.Orientation;
                //ts.HeadPose.AngularVelocity
                //rotation en quaternion 0.7 quand 90°
                cout << std::fixed << std::setprecision(0) << "Orientation (x,y,z,w):  "
                     << COLW << (tempOrient.x*90)/0.7 << ","
                     << COLW << (tempOrient.y*90)/0.7 << "," << COLW << (tempOrient.z*90)/0.7
                     << "," << COLW << tempOrient.w << endl;


                // Wait a bit to let us actually read stuff.
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }

            ovr_Destroy(session);
        }

        ovr_Shutdown();
        // If we've fallen through to this point, the HMD is no longer
        // connected.
    }

    return 0;
}
