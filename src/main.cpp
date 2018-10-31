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

//#define MAIN

/*
 * main.cpp
 *
 * This file describes the general "gameplay" of the app. At this point,
 * this involves initialization of the engine and keystroke handling.
 *
 */

int degrees = 0;

#include <math.h>

#include <iostream>

#include "World.h"
#include "Engine.h"

#define ESCAPE 27
#define PAGE_UP 73
#define PAGE_DOWN 81
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77

GLfloat movementSpeedFactor = 3.0f;

bool location_allowed(float x, float z)
{
    //cout << "x=" << x << ",z=" << z << ",rot=" << Engine::rot << endl;
    //return true;
    int box_x = floor(x), box_z = floor(z);
    if(box_x >= 0 && box_x <= World::max_x &&
            box_z >= 0 && box_z <= World::max_z)
        return World::lines[box_x][box_z] != 'x';
    return false;
}

float toRads(const float &theAngleInDegrees) {
    return theAngleInDegrees * 3.141592654f / 180.0f;
}

const float PI_OVER180 = 0.0174532925f;

void keyPressed(unsigned char key, int x, int y)
{
    float pitchFactor = cos(toRads(Engine::camera.rotateX));
    float move_x = -((movementSpeedFactor * float(sin(toRads(Engine::camera.rotateY)))) * pitchFactor) * 0.1f;
    float move_z = -((movementSpeedFactor * float(cos(toRads(Engine::camera.rotateY))) * -1.0f) * pitchFactor) * 0.1f;

    switch (key) {
        case GLUT_KEY_PAGE_UP:
            Engine::camera.rotateX -= 1.0f;
            break;

        case GLUT_KEY_PAGE_DOWN:
            Engine::camera.rotateX += 1.0f;
            break;

        case GLUT_KEY_UP:

            if(location_allowed(
                        Engine::camera.xpos-(3.0*move_x),
                        Engine::camera.zpos-(3.0*move_z)))
            {
                Engine::camera.xpos -= move_x;
                Engine::camera.zpos -= move_z;
            }
            break;

        case GLUT_KEY_DOWN:
            if(location_allowed(
                        Engine::camera.xpos+(3.0*move_x),
                        Engine::camera.zpos+(3.0*move_z)))
            {
                Engine::camera.xpos += move_x;
                Engine::camera.zpos += move_z;
            }
            break;

        case GLUT_KEY_LEFT:
            //Engine::objects[0].rotateDegrees(degrees);
            degrees++;
            Engine::camera.rotateY -= 3.0f;
            break;

        case GLUT_KEY_RIGHT:
            //Engine::objects[0].rotateDegrees(degrees);
            degrees--;
            Engine::camera.rotateY += 3.0f;
            break;

        case ' ':
            Engine::camera.ypos += 0.1f;
            break;

        case 'c':
            Engine::camera.ypos -= 0.1f;
            break;

        case 'z':
            Engine::rot -= 1.0;
            break;

        case 'x':
            Engine::rot += 1.0;
            break;

        case ESCAPE:
        case 'q':
            exit(1);
    }
}

int main(int argc, char **argv)
{
    Engine engine(320,240,false);
    Engine::rot = 0;
    engine.bindKeyHandler(&keyPressed);
    engine.mainLoop();
    return 0;
}
