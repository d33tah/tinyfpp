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
