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

#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include "World.h"
#include "Camera.h"
#include "Object.h"

class Engine
{
    /*
     * Engine
     *
     * Responsibilities of this class:
     *
     * - graphics initialization
     * - drawing the world
     *
     * In the future, it is planned to split this into Renderer and Engine
     * or Game and Engine classes.
     *
     */
    private:

        static GLuint texture;
        static World world;

        GLvoid loadGLTextures();
        GLvoid initGL(GLsizei width, GLsizei height);

        static void resizeGLScene(GLsizei width, GLsizei height);
        static void drawGLScene();

    public:
        static double rot;
        static vector<Object> objects;
        static void loadObjects();

        static void (*fun)(unsigned char,int,int);
        static Camera camera;

        Engine(int width,int height,bool fullscreen);
        void bindKeyHandler(void (*fun)(unsigned char,int,int));
        void mainLoop();

        static GLint windowWidth;
        static GLint windowHeight;

};

#endif
