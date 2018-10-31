import sys
import pygame
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

TRIANGLES = []
im = 0

def load_maze():
    global TRIANGLES
    with open('Data/maze.txt') as f:
        for x, line in enumerate(f):
            for z, c in enumerate(line.rstrip()):

                TRIANGLES.append(
                    [{'u': 0.0, 'v': 0.0, 'x': x, 'y': 0.0, 'z': z},
                     {'u': 0.0, 'v': 0.0, 'x': x + 1.0, 'y': 0.0, 'z': z},
                     {'u': 0.0, 'v': 0.0, 'x': x + 1.0, 'y': 0.0, 'z': z + 1.0}]
                )

                TRIANGLES.append(
                    [{'u': 0.0, 'v': 0.0, 'x': x, 'y': 0.0, 'z': z},
                     {'u': 0.0, 'v': 0.0, 'x': x, 'y': 0.0, 'z': z + 1.0},
                     {'u': 0.0, 'v': 0.0, 'x': x + 1.0, 'y': 0.0, 'z': z + 1.0}]
                )

                TRIANGLES.append(
                    [{'u': 0.0, 'v': 0.0, 'x': x, 'y': 1.0, 'z': z},
                     {'u': 0.0, 'v': 0.0, 'x': x + 1.0, 'y': 1.0, 'z': z},
                     {'u': 0.0, 'v': 0.0, 'x': x + 1.0, 'y': 1.0, 'z': z + 1.0}]
                )

                TRIANGLES.append(
                    [{'u': 0.0, 'v': 0.0, 'x': x, 'y': 1.0, 'z': z},
                     {'u': 0.0, 'v': 0.0, 'x': x, 'y': 1.0, 'z': z + 1.0},
                     {'u': 0.0, 'v': 0.0, 'x': x + 1.0, 'y': 1.0, 'z': z + 1.0}]
                )

                if c == ' ':
                    continue

                TRIANGLES.append([{'x': x + 1.0,
                                   'y': 1.0,
                                   'z': z,
                                   'u': 0.0,
                                   'v': 1.0},
                                  {'x': x + 1.0,
                                   'y': 0.0,
                                   'z': z,
                                   'u': 0.0,
                                   'v': 0.0},
                                  {'x': x,
                                   'y': 0.0,
                                   'z': z,
                                   'u': 1.5,
                                   'v': 0.0}])
                TRIANGLES.append([{'x': x + 1.0,
                                   'y': 1.0,
                                   'z': z,
                                   'u': 0.0,
                                   'v': 1.0},
                                  {'x': x,
                                   'y': 1.0,
                                   'z': z,
                                   'u': 1.5,
                                   'v': 1.0},
                                  {'x': x,
                                   'y': 0.0,
                                   'z': z,
                                   'u': 1.5,
                                   'v': 0.0}])
                TRIANGLES.append([{'x': x + 1.0,
                                   'y': 1.0,
                                   'z': z + 1.0,
                                   'u': 0.0,
                                   'v': 1.0},
                                  {'x': x + 1.0,
                                   'y': 0.0,
                                   'z': z + 1.0,
                                   'u': 0.0,
                                   'v': 0.0},
                                  {'x': x + 1.0,
                                   'y': 0.0,
                                   'z': z,
                                   'u': 1.5,
                                   'v': 0.0}])
                TRIANGLES.append([{'x': x + 1.0,
                                   'y': 1.0,
                                   'z': z + 1.0,
                                   'u': 0.0,
                                   'v': 1.0},
                                  {'x': x + 1.0,
                                   'y': 1.0,
                                   'z': z,
                                   'u': 1.5,
                                   'v': 1.0},
                                  {'x': x + 1.0,
                                   'y': 0.0,
                                   'z': z,
                                   'u': 1.5,
                                   'v': 0.0}])
                TRIANGLES.append([{'x': x,
                                   'y': 1.0,
                                   'z': z + 1.0,
                                   'u': 0.0,
                                   'v': 1.0},
                                  {'x': x,
                                   'y': 0.0,
                                   'z': z + 1.0,
                                   'u': 0.0,
                                   'v': 0.0},
                                  {'x': x,
                                   'y': 0.0,
                                   'z': z,
                                   'u': 1.5,
                                   'v': 0.0}])
                TRIANGLES.append([{'x': x,
                                   'y': 1.0,
                                   'z': z + 1.0,
                                   'u': 0.0,
                                   'v': 1.0},
                                  {'x': x,
                                   'y': 1.0,
                                   'z': z,
                                   'u': 1.5,
                                   'v': 1.0},
                                  {'x': x,
                                   'y': 0.0,
                                   'z': z,
                                   'u': 1.5,
                                   'v': 0.0}])
                TRIANGLES.append([{'x': x + 1.0,
                                   'y': 1.0,
                                   'z': z + 1.0,
                                   'u': 0.0,
                                   'v': 1.0},
                                  {'x': x + 1.0,
                                   'y': 0.0,
                                   'z': z + 1.0,
                                   'u': 0.0,
                                   'v': 0.0},
                                  {'x': x,
                                   'y': 0.0,
                                   'z': z + 1.0,
                                   'u': 1.5,
                                   'v': 0.0}])
                TRIANGLES.append([{'x': x + 1.0,
                                   'y': 1.0,
                                   'z': z + 1.0,
                                   'u': 0.0,
                                   'v': 1.0},
                                  {'x': x,
                                   'y': 1.0,
                                   'z': z + 1.0,
                                   'u': 1.5,
                                   'v': 1.0},
                                  {'x': x,
                                   'y': 0.0,
                                   'z': z + 1.0,
                                   'u': 1.5,
                                   'v': 0.0}])
    return TRIANGLES

def setup_textures():
    global im
    img = pygame.image.load('Data/texture.bmp')
    textureData = pygame.image.tostring(img, "RGB", 1)
    width = img.get_width()
    height = img.get_height()

    im = glGenTextures(1)
    glBindTexture(GL_TEXTURE_2D, im)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST)
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData)


def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()

    camera_x, camera_y, camera_z = (-0.5,0.5,0.5)
    xtrans, ytrans, ztrans = -camera_x, -camera_y, -camera_z
    glTranslatef(xtrans, ytrans, ztrans)

    rotateX = 0
    rotateY = 180
    glRotatef(rotateX, 1.0, 0, 0)
    glRotatef(rotateY, 0, 1.0, 0)

    glBindTexture(GL_TEXTURE_2D, im)

    for triangle in TRIANGLES:
        glBegin(GL_TRIANGLES)
        glNormal3f( 0.0, 0.0, 1.0)

        for i in range(3):
            t = triangle[i]
            glTexCoord2f(t['u'], t['v'])
            glVertex3f(t['x'], t['y'], t['z'])

        glEnd()
    glutSwapBuffers()

def initGL():
    glEnable(GL_TEXTURE_2D)
    glEnable(GL_DEPTH_TEST)

    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(45, 1, 0.05, 100)

    glMatrixMode(GL_MODELVIEW)


def main():
    TRIANGLES = load_maze()
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH)
    glutCreateWindow('interactive')
    glutDisplayFunc(display)
    setup_textures()
    initGL()
    glutIdleFunc(display);
    glutMainLoop()


if __name__ == '__main__':
    main()
