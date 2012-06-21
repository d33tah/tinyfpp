#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <GL/gl.h>

class Camera
{
    public:

        Camera() { 
            rotateY = 0.0; 
            rotateX = 0.0;
            camx = 0;
            camy = 0;
            camz = 0;
        }

        float xpos, zpos;
        GLfloat rotateX, rotateY, camx, camy, camz;

};

#endif
