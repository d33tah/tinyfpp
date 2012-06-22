#ifndef __CAMERASYNC_H__
#define __CAMERASYNC_H__

#include "Camera.h"

class CameraSync
{
    private:
        Camera& camera;
        int sock;
    public:
        CameraSync(Camera& camera);
        void sendSync(Camera camera2);
};

#endif
