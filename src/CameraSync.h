/*
This file is part of tinyfpp.

tinyfpp is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

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
