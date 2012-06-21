#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "World.h"
#include "Triangle.h"
#include "Image.h"
#include "Camera.h"

#define ESCAPE 27
#define PAGE_UP 73
#define PAGE_DOWN 81
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77

const float piover180 = 0.0174532925f;

GLuint texture;
World world;
Camera camera;

GLvoid LoadGLTextures()
{	
    Image* image = new Image;
    image->FromBMP("Data/mud.bmp");

    glGenTextures(3, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image->sizeX, image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
};

GLvoid clearScreen(GLsizei Width, GLsizei Height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
}

GLvoid InitGL(GLsizei Width, GLsizei Height)
{
    LoadGLTextures();
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    clearScreen(Width, Height);

}

GLvoid ReSizeGLScene(GLsizei Width, GLsizei Height)
{
    if (Height==0)
        Height=1;

    glViewport(0, 0, Width, Height);
    clearScreen(Width, Height);
}

GLvoid DrawGLScene()
{
    GLfloat sceneroty;

    GLfloat xtrans = -camera.xpos;
    GLfloat ztrans = -camera.zpos;
    GLfloat ytrans = -0.5f;
    sceneroty = 360.0f - camera.rotateX;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(camera.rotateY, 1.0f, 0, 0);
    glRotatef(sceneroty, 0, 1.0f, 0);

    glTranslatef(xtrans, ytrans, ztrans);

    glBindTexture(GL_TEXTURE_2D, texture);

    for (int loop=0; loop<world.numtriangles; loop++)
    {
        GLfloat x_m, y_m, z_m, u_m, v_m;

        glBegin(GL_TRIANGLES);		
        glNormal3f( 0.0f, 0.0f, 1.0f);

        x_m = world.triangle[loop].vertex[0].x;
        y_m = world.triangle[loop].vertex[0].y;
        z_m = world.triangle[loop].vertex[0].z;
        u_m = world.triangle[loop].vertex[0].u;
        v_m = world.triangle[loop].vertex[0].v;
        glTexCoord2f(u_m,v_m);
        glVertex3f(x_m,y_m,z_m);

        x_m = world.triangle[loop].vertex[1].x;
        y_m = world.triangle[loop].vertex[1].y;
        z_m = world.triangle[loop].vertex[1].z;
        u_m = world.triangle[loop].vertex[1].u;
        v_m = world.triangle[loop].vertex[1].v;
        glTexCoord2f(u_m,v_m);
        glVertex3f(x_m,y_m,z_m);

        x_m = world.triangle[loop].vertex[2].x;
        y_m = world.triangle[loop].vertex[2].y;
        z_m = world.triangle[loop].vertex[2].z;
        u_m = world.triangle[loop].vertex[2].u;
        v_m = world.triangle[loop].vertex[2].v;
        glTexCoord2f(u_m,v_m);
        glVertex3f(x_m,y_m,z_m);	

        glEnd();	
    }

    glutSwapBuffers();
}

void specialKeyPressed(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_PAGE_UP:
            camera.rotateY -= 0.2f;
            break;

        case GLUT_KEY_PAGE_DOWN:
            camera.rotateY += 1.0f;
            break;

        case GLUT_KEY_UP:
            camera.xpos -= (float)sin(camera.rotateX*piover180) * 0.05f;
            camera.zpos -= (float)cos(camera.rotateX*piover180) * 0.05f;	
            break;

        case GLUT_KEY_DOWN:
            camera.xpos += (float)sin(camera.rotateX*piover180) * 0.05f;
            camera.zpos += (float)cos(camera.rotateX*piover180) * 0.05f;	
            break;

        case GLUT_KEY_LEFT:
            camera.rotateX += 1.5f;
            break;

        case GLUT_KEY_RIGHT:
            camera.rotateX -= 1.5f;
            break;

        case ESCAPE:
            exit(1);                   	
    }	
}

inline void keyPressed(unsigned char key, int x, int y)
{
    specialKeyPressed(key,x,y);
}

int main(int argc, char **argv)
{
    int y = 320;
    int x = 240;
    world.SetupWorld();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);
    glutInitWindowSize(y,x);
    //glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Tytul okna");
    glutDisplayFunc(&DrawGLScene);
    //glutFullScreen();
    glutIdleFunc(&DrawGLScene);
    glutReshapeFunc(&ReSizeGLScene);
    glutKeyboardFunc(&keyPressed);
    glutSpecialFunc(&specialKeyPressed);
    InitGL(y,x);
    glutMainLoop();
    return 1;
}
