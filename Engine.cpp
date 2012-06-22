#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "World.h"
#include "Triangle.h"
#include "Image.h"
#include "Camera.h"
#include "Engine.h"

GLuint Engine::texture;
Camera Engine::camera;
CameraSync Engine::cam_sync(Engine::camera);

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

GLvoid Engine::LoadGLTextures()
{	
    Image* image = new Image;
    image->FromBMP("Data/mud.bmp");

    glGenTextures(3, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image->sizeX, image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
};

GLvoid Engine::clearScreen(GLsizei width, GLsizei height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
}

GLvoid Engine::InitGL(GLsizei width, GLsizei height)
{
    LoadGLTextures();
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    clearScreen(width, height);

}

void Engine::ReSizeGLScene(GLsizei width, GLsizei height)
{
    if (height==0)
        height=1;

    glViewport(0, 0, width, height);
    clearScreen(width, height);
}

void Engine::DrawGLScene()
{
    GLfloat sceneroty;

    GLfloat xtrans = -camera.xpos;
    GLfloat ztrans = -camera.zpos;
    GLfloat ytrans = -camera.ypos;
    sceneroty = 360.0f - camera.rotateX;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(camera.rotateY, 1.0f, 0, 0);
    glRotatef(sceneroty, 0, 1.0f, 0);

    glTranslatef(xtrans, ytrans, ztrans);

    glBindTexture(GL_TEXTURE_2D, texture);

    for (int loop=0; loop<World::numtriangles; loop++)
    {
        GLfloat x_m, y_m, z_m, u_m, v_m;

        glBegin(GL_TRIANGLES);		
        glNormal3f( 0.0f, 0.0f, 1.0f);

        x_m = World::triangle[loop].vertex[0].x;
        y_m = World::triangle[loop].vertex[0].y;
        z_m = World::triangle[loop].vertex[0].z;
        u_m = World::triangle[loop].vertex[0].u;
        v_m = World::triangle[loop].vertex[0].v;
        glTexCoord2f(u_m,v_m);
        glVertex3f(x_m,y_m,z_m);

        x_m = World::triangle[loop].vertex[1].x;
        y_m = World::triangle[loop].vertex[1].y;
        z_m = World::triangle[loop].vertex[1].z;
        u_m = World::triangle[loop].vertex[1].u;
        v_m = World::triangle[loop].vertex[1].v;
        glTexCoord2f(u_m,v_m);
        glVertex3f(x_m,y_m,z_m);

        x_m = World::triangle[loop].vertex[2].x;
        y_m = World::triangle[loop].vertex[2].y;
        z_m = World::triangle[loop].vertex[2].z;
        u_m = World::triangle[loop].vertex[2].u;
        v_m = World::triangle[loop].vertex[2].v;
        glTexCoord2f(u_m,v_m);
        glVertex3f(x_m,y_m,z_m);	

        glEnd();	
    }

    glutSwapBuffers();
}

Engine::Engine(int x, int y, bool fullscreen)
{
    World::SetupWorld();
    int argc = 0;
    char argv = '\0';
    char* c_argv = &argv;
    glutInit(&argc, &c_argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);
    glutInitWindowSize(x,y);
    //glutInitWindowSize(640, 480);
    //glutInitWindowPosition(0, 0);
    glutCreateWindow("Tytul okna");
    glutDisplayFunc(&Engine::DrawGLScene);
    if(fullscreen)
        glutFullScreen();
    glutIdleFunc(&Engine::DrawGLScene);
    glutReshapeFunc(&Engine::ReSizeGLScene);
    InitGL(y,x);
}

