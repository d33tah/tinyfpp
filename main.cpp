/*
 * main.cpp
 *
 * This file describes the general "gameplay" of the app. At this point,
 * this involves initialization of the engine and keystroke handling.
 *
 */

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


bool location_allowed(float x, float z)
{
    int box_x = floor(x);
    int box_z = floor(z);
    if(box_x>=0 && box_x<=World::max_x && box_z>=0 && box_z<=World::max_z)
    {
        if (World::lines[box_x][box_z]=='x')
        {
            return true;
        }
    }
    return false;
}

const float PI_OVER180 = 0.0174532925f;

void keyPressed(unsigned char key, int x, int y)
{
    float move_x = sin(Engine::camera.rotateX * PI_OVER180 ) * 0.05f;
    float move_z = cos(Engine::camera.rotateX * PI_OVER180 ) * 0.05f;
    switch (key) {
        case GLUT_KEY_PAGE_UP:
            Engine::camera.rotateY -= 1.0f;
            Engine::cam_sync.sendSync(Engine::camera);
            break;

        case GLUT_KEY_PAGE_DOWN:
            Engine::camera.rotateY += 1.0f;
            Engine::cam_sync.sendSync(Engine::camera);
            break;

        case GLUT_KEY_UP:

            if(location_allowed(
                        Engine::camera.xpos-move_x, Engine::camera.zpos-move_z))
            {
                Engine::camera.xpos -= move_x;
                Engine::camera.zpos -= move_z; 
                Engine::cam_sync.sendSync(Engine::camera);
            }
            break;

        case GLUT_KEY_DOWN:
            if(location_allowed(
                        Engine::camera.xpos+move_x, Engine::camera.zpos+move_z))
            {
                Engine::camera.xpos += move_x;
                Engine::camera.zpos += move_z;
                Engine::cam_sync.sendSync(Engine::camera);
            }
            break;

        case GLUT_KEY_LEFT:
            Engine::camera.rotateX += 3.0f;
            Engine::cam_sync.sendSync(Engine::camera);
            break;

        case GLUT_KEY_RIGHT:
            Engine::camera.rotateX -= 3.0f;
            Engine::cam_sync.sendSync(Engine::camera);
            break;

        case ' ':
            Engine::camera.ypos += 0.1f;
            break;

        case 'c':
            Engine::camera.ypos -= 0.1f;
            break;

        case ESCAPE:
        case 'q':
            exit(1);                   	
    }	
}

int main(int argc, char **argv)
{
    Engine engine(320,240,false);
    engine.bindKeyHandler(&keyPressed);
    engine.mainLoop();
    return 0;
}
