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

#include <iostream>
#include <fstream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include "World.h"
#include "Triangle.h"
#include "Image.h"
#include "Camera.h"
#include "Engine.h"

GLuint Engine::texture;
Camera Engine::camera;
CameraSync Engine::cam_sync(Engine::camera);
vector<Object> Engine::objects;
double Engine::rot;
GLint Engine::windowWidth = 800;
GLint Engine::windowHeight = 600;

void (*Engine::fun)(unsigned char,int,int);

void Engine::mainLoop()
{
    glutMainLoop();
}

inline void specialKeyPressed(int key, int x, int y)
{
    Engine::fun(key,x,y);
}

void Engine::bindKeyHandler(void (*_fun)(unsigned char,int,int))
{
    Engine::fun=_fun;
    glutKeyboardFunc(fun);
    glutSpecialFunc(&specialKeyPressed);
}

void mouseMovement(int mouseX, int mouseY)
{
    GLfloat vertMouseSensitivity  = 10.0f;
    GLfloat horizMouseSensitivity = 10.0f;

    int horizMovement = mouseX - Engine::windowWidth / 2;
    int vertMovement  = mouseY - Engine::windowHeight / 2;

    //TODO: investigate why the code breaks if I comment out this condition.
    if (horizMovement == 0 && vertMovement == 0)
        return;

    Engine::camera.rotateX += vertMovement / vertMouseSensitivity;
    Engine::camera.rotateY += horizMovement / horizMouseSensitivity;

    // Control looking up and down with the mouse forward/back movement

    // Looking left and right. Keep the angles in the range -180.0f (anticlockwise turn looking behind) to 180.0f (clockwise turn looking behind)
    if (Engine::camera.rotateY < -180.0f)
        Engine::camera.rotateY += 360.0f;

    if (Engine::camera.rotateY > 180.0f)
        Engine::camera.rotateY -= 360.0f;

    if (Engine::camera.rotateX < -90.0f)
        Engine::camera.rotateX = -90.0f;

    if (Engine::camera.rotateX > 90.0f)
        Engine::camera.rotateX = 90.0f;

    glutWarpPointer(Engine::windowWidth/2, Engine::windowHeight/2);
}

GLvoid Engine::loadGLTextures()
{
    Image* image = new Image;
    image->fromBMP("Data/texture.bmp");

    glGenTextures(3, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image->sizeX, image->sizeY, 0, GL_RGB,
            GL_UNSIGNED_BYTE, image->data);
};

GLvoid Engine::clearScreen(GLsizei width, GLsizei height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
}

GLvoid Engine::initGL(GLsizei width, GLsizei height)
{
    loadGLTextures();
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glutWarpPointer(Engine::windowWidth/2, Engine::windowHeight/2);
    glutSetCursor (GLUT_CURSOR_NONE);
    clearScreen(width, height);

}

void Engine::resizeGLScene(GLsizei width, GLsizei height)
{
    if (height==0)
        height=1;

    glViewport(0, 0, width, height);
    clearScreen(width, height);

    windowHeight = height;
    windowWidth = width;
}

void Engine::drawGLScene()
{
    GLfloat sceneroty;

    GLfloat xtrans = -camera.xpos;
    GLfloat ztrans = -camera.zpos;
    GLfloat ytrans = -camera.ypos;
    sceneroty = camera.rotateY;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(camera.rotateX, 1.0f, 0, 0);
    glRotatef(sceneroty, 0, 1.0f, 0);

    glTranslatef(xtrans, ytrans, ztrans);

    glBindTexture(GL_TEXTURE_2D, texture);

    for (unsigned int loop=0; loop<World::triangle.size(); loop++)
    {
        Triangle tr = World::triangle[loop];
        GLfloat x_m, y_m, z_m, u_m, v_m;

        glBegin(GL_TRIANGLES);
        glNormal3f( 0.0f, 0.0f, 1.0f);

       for(int vv=0; vv<3; vv++)

        x_m = tr.vertex[0].x;
        y_m = tr.vertex[0].y;
        z_m = tr.vertex[0].z;
        u_m = tr.vertex[0].u;
        v_m = tr.vertex[0].v;
        glTexCoord2f(u_m,v_m);
        glVertex3f(x_m,y_m,z_m);

        x_m = tr.vertex[1].x;
        y_m = tr.vertex[1].y;
        z_m = tr.vertex[1].z;
        u_m = tr.vertex[1].u;
        v_m = tr.vertex[1].v;
        glTexCoord2f(u_m,v_m);
        glVertex3f(x_m,y_m,z_m);

        x_m = tr.vertex[2].x;
        y_m = tr.vertex[2].y;
        z_m = tr.vertex[2].z;
        u_m = tr.vertex[2].u;
        v_m = tr.vertex[2].v;
        glTexCoord2f(u_m,v_m);
        glVertex3f(x_m,y_m,z_m);

        glEnd();
    }

    for(unsigned int i = 0; i<objects.size(); i++)
    {
        int x = objects[i].point.x, y = objects[i].point.y, z = objects[i].point.z;
        vector<Triangle> triangles = objects[i].getTriangles();
        for (unsigned int loop=0; loop<triangles.size(); loop++)
        {
            Triangle tr = triangles[loop];
            GLfloat x_m, y_m, z_m, u_m, v_m;

            glBegin(GL_TRIANGLES);
            glNormal3f( 0.0f, 0.0f, 1.0f);

        for(int vv=0; vv<3; vv++)

            x_m = tr.vertex[0].x+x;
            y_m = tr.vertex[0].y+y;
            z_m = tr.vertex[0].z+z;
            u_m = tr.vertex[0].u;
            v_m = tr.vertex[0].v;
            glTexCoord2f(u_m,v_m);
            glVertex3f(x_m,y_m,z_m);

            x_m = tr.vertex[1].x+x;
            y_m = tr.vertex[1].y+y;
            z_m = tr.vertex[1].z+z;
            u_m = tr.vertex[1].u;
            v_m = tr.vertex[1].v;
            glTexCoord2f(u_m,v_m);
            glVertex3f(x_m,y_m,z_m);

            x_m = tr.vertex[2].x+x;
            y_m = tr.vertex[2].y+y;
            z_m = tr.vertex[2].z+z;
            u_m = tr.vertex[2].u;
            v_m = tr.vertex[2].v;
            glTexCoord2f(u_m,v_m);
            glVertex3f(x_m,y_m,z_m);

            glEnd();
        }

    }

    glutWarpPointer(Engine::windowWidth/2, Engine::windowHeight/2);
    glutSwapBuffers();
}

void Engine::loadObjects()
{
    ifstream file("Data/objects.txt");
    if (!file) {
        cerr << "FATAL: Could not open Data/objects.txt." << endl;
        exit(1);
    }
    for(;;)
    {
        string filename;
        file >> filename;
        if(!file.good())
            break;

        Object obj;
        obj.loadFile(filename);

        Vertex v;
        file >> v.x;
        file >> v.y;
        file >> v.z;
        obj.point = v;

        objects.push_back(obj);
    }
}

Engine::Engine(int x, int y, bool fullscreen)
{
    windowWidth = x;
    windowHeight = y;

    //Engine::loadObjects();
    World::setupWorld();
    int argc = 0;
    char argv = '\0';
    char* c_argv = &argv;
    glutInit(&argc, &c_argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);
    glutInitWindowSize(x,y);
    //glutInitWindowSize(640, 480);
    //glutInitWindowPosition(0, 0);
    glutCreateWindow("tinyfpp");
    glutDisplayFunc(&Engine::drawGLScene);
    if(fullscreen)
        glutFullScreen();
    glutIdleFunc(&Engine::drawGLScene);
    glutReshapeFunc(&Engine::resizeGLScene);
    glutPassiveMotionFunc(mouseMovement);
    initGL(y,x);
}

