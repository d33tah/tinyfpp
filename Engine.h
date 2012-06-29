#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "World.h"
#include "Camera.h"
#include "CameraSync.h"
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
     * - wrapping up world, camera and camera_sync data.
     *
     * In the future, it is planned to split this into Renderer and Engine
     * or Game and Engine classes.
     *
     */
    private:
        static GLuint texture;
        static World world;

        GLvoid loadGLTextures();
        static GLvoid clearScreen(GLsizei width, GLsizei height);
        GLvoid initGL(GLsizei width, GLsizei height);

        static void resizeGLScene(GLsizei width, GLsizei height);
        static void drawGLScene();

        static vector<Object> objects;
        static void loadObjects();

    public:
        static void (*fun)(unsigned char,int,int);
        static CameraSync cam_sync;
        static Camera camera;

        Engine(int width,int height,bool fullscreen);
        void bindKeyHandler(void (*fun)(unsigned char,int,int));
        void mainLoop();

};

/*
GLuint Engine::texture;
Camera Engine::camera;
CameraSync Engine::cam_sync(Engine::camera);
vector<Object> Engine::objects;
*/

#endif
