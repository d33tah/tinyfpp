#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <GL/gl.h>

class Camera
{
    public:

        Camera() {
            rotateX = 0.0;
            rotateY = 180.0;
            camx = 0;
            camy = 0;
            camz = 0.0;
            zpos = 0.5;
            ypos = 0.5;
            xpos = 0.5;
        }

        float xpos, zpos, ypos;
        GLfloat rotateX, rotateY, camx, camy, camz;

};

#endif
