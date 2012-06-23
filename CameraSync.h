#ifndef __CAMERASYNC_H__
#define __CAMERASYNC_H__

#include "Camera.h"

class CameraSync
{
    /*
     * CameraSync is a class used for synchronizing the cameras between 
     * clients. The code is planned to be multiplatform.
     *
     */

    private:
        Camera& camera;
        int sock;
    public:
        CameraSync(Camera& camera);
        void sendSync(Camera camera2);
};

#endif
