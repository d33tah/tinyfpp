#include <iostream>

#include <GL/glfw.h>      // Include OpenGL Framework library
#include <math.h>         // Used only for sin() and cos() functions
#include <cstdlib>        // exit()

using namespace std;

const float TO_RADS = 3.141592654f / 180.0f; // The value of 1 degree in radians

GLint windowWidth  = 800;                    // Width of our window
GLint windowHeight = 600;                    // Heightof our window

GLint midWindowX = windowWidth  / 2;         // Middle of the window horizontally
GLint midWindowY = windowHeight / 2;         // Middle of the window vertically

GLfloat fieldOfView = 45.0f;                 // Define our field of view (i.e. how quickly foreshortening occurs)
GLfloat near        = 1.0f;                  // The near (Z Axis) point of our viewing frustrum (default 1.0f)
GLfloat far         = 1500.0f;               // The far  (Z Axis) point of our viewing frustrum (default 1500.0f)

GLfloat camXRot = 0.0f, camYRot = 0.0f, camZRot = 0.0f;
GLfloat camXPos = 0.0f, camYPos = 0.0f, camZPos = 0.0f;
GLfloat camXSpeed = 0.0f, camYSpeed = 0.0f, camZSpeed = 0.0f;

GLfloat movementSpeedFactor = 3.0f;

bool holdingForward = false, holdingBackward = false,
     holdingLeftStrafe = false, holdingRightStrafe = false;

float toRads(const float &theAngleInDegrees) {
    return theAngleInDegrees * TO_RADS;
}

void checkGLError(const char * errorLocation) {
    unsigned int gle = glGetError();

    if (gle != GL_NO_ERROR) {
        cerr << "GL Error discovered from caller " << errorLocation << ": " << gle << endl;
        exit(1);
    }
}

// Function to move the camera the amount we've calculated in the calculateCameraMovement function
void moveCamera() {
    // Break up our movement into components along the X, Y and Z axis
    float camMovementXComponent = 0.0f;
    float camMovementYComponent = 0.0f;
    float camMovementZComponent = 0.0f;

    if (holdingForward == true) {
        // Control X-Axis movement
        float pitchFactor = cos(toRads(camXRot));
        camMovementXComponent += ( movementSpeedFactor * float(sin(toRads(camYRot))) ) * pitchFactor;

        // Control Y-Axis movement
        camMovementYComponent += movementSpeedFactor * float(sin(toRads(camXRot))) * -1.0f;

        // Control Z-Axis movement
        float yawFactor = float(cos(toRads(camXRot)));
        camMovementZComponent += ( movementSpeedFactor * float(cos(toRads(camYRot))) * -1.0f ) * yawFactor;
    }

    if (holdingBackward == true) {
        // Control X-Axis movement
        float pitchFactor = cos(toRads(camXRot));
        camMovementXComponent += ( movementSpeedFactor * float(sin(toRads(camYRot))) * -1.0f) * pitchFactor;

        // Control Y-Axis movement
        camMovementYComponent += movementSpeedFactor * float(sin(toRads(camXRot)));

        // Control Z-Axis movement
        float yawFactor = float(cos(toRads(camXRot)));
        camMovementZComponent += ( movementSpeedFactor * float(cos(toRads(camYRot))) ) * yawFactor;
    }

    if (holdingLeftStrafe == true) {
        float yRotRad = toRads(camYRot);

        camMovementXComponent += -movementSpeedFactor * float(cos(yRotRad));
        camMovementZComponent += -movementSpeedFactor * float(sin(yRotRad));
    }

    if (holdingRightStrafe == true) {
        float yRotRad = toRads(camYRot);

        camMovementXComponent += movementSpeedFactor * float(cos(yRotRad));
        camMovementZComponent += movementSpeedFactor * float(sin(yRotRad));
    }

    // After combining our movements for any & all keys pressed, assign them to our camera speed along the given axis
    camXSpeed = camMovementXComponent;
    camYSpeed = camMovementYComponent;
    camZSpeed = camMovementZComponent;

    // Cap the speeds to our movementSpeedFactor (otherwise going forward and strafing at an angle is twice as fast as just going forward!)
    // X Speed cap
    if (camXSpeed > movementSpeedFactor)
        camXSpeed = movementSpeedFactor;
    if (camXSpeed < -movementSpeedFactor)
        camXSpeed = -movementSpeedFactor;

    if (camYSpeed > movementSpeedFactor)
        camYSpeed = movementSpeedFactor;
    if (camYSpeed < -movementSpeedFactor)
        camYSpeed = -movementSpeedFactor;

    if (camZSpeed > movementSpeedFactor)
        camZSpeed = movementSpeedFactor;
    if (camZSpeed < -movementSpeedFactor)
        camZSpeed = -movementSpeedFactor;

    camXPos += camXSpeed;
    camYPos += camYSpeed;
    camZPos += camZSpeed;
}

void handleMouseMove(int mouseX, int mouseY) {
    GLfloat vertMouseSensitivity  = 10.0f;
    GLfloat horizMouseSensitivity = 10.0f;

    int horizMovement = mouseX - midWindowX;
    int vertMovement  = mouseY - midWindowY;

    camXRot += vertMovement / vertMouseSensitivity;
    camYRot += horizMovement / horizMouseSensitivity;

    // Control looking up and down with the mouse forward/back movement
    if (camXRot < -90.0f)
        camXRot = -90.0f;

    if (camXRot > 90.0f)
        camXRot = 90.0f;

    // Looking left and right. Keep the angles in the range -180.0f (anticlockwise turn looking behind) to 180.0f (clockwise turn looking behind)
    if (camYRot < -180.0f)
        camYRot += 360.0f;

    if (camYRot > 180.0f)
        camYRot -= 360.0f;

    glfwSetMousePos(midWindowX, midWindowY);
}

void handleKeypress(int theKey, int theAction) {
    if (theAction == GLFW_PRESS) {
        if (theKey == 'W')
            holdingForward = true;
        else if (theKey == 'S')
            holdingBackward = true;
        else if (theKey == 'A')
            holdingLeftStrafe = true;
        else if (theKey == 'D')
            holdingRightStrafe = true;
    } else {
        if (theKey == 'W')
            holdingForward = false;
        else if (theKey == 'S')
            holdingBackward = false;
        else if (theKey == 'A')
            holdingLeftStrafe = false;
        else if (theKey == 'D')
            holdingRightStrafe = false;
    }
}

void drawScene() {
    // Clear the screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset the matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Move the camera to our location in space
    glRotatef(camXRot, 1.0f, 0.0f, 0.0f);        // Rotate our camera on the x-axis (looking up and down)
    glRotatef(camYRot, 0.0f, 1.0f, 0.0f);        // Rotate our camera on the  y-axis (looking left and right)
    glTranslatef(-camXPos,-camYPos,-camZPos);    // Translate the modelviewm matrix to the position of our camera

    GLfloat extent      = 600.0f; // How far on the Z-Axis and X-Axis the ground extends
    GLfloat stepSize    = 20.0f;  // The size of the separation between points
    GLfloat groundLevel = -50.0f;   // Where on the Y-Axis the ground is drawn

    // Draw our ground grid
    glBegin(GL_LINES);
    for (GLint loop = -extent; loop < extent; loop += stepSize)
    {
        // Draw lines along Z-Axis
        glVertex3f(loop, groundLevel,  extent);
        glVertex3f(loop, groundLevel, -extent);

        // Draw lines across X-Axis
        glVertex3f(-extent, groundLevel, loop);
        glVertex3f(extent,  groundLevel, loop);
    }
    glEnd();

    glfwSwapBuffers(); // Swap the buffers to display the scene (so we don't have to watch it being drawn!)
}

int main(int argc, char **argv) {
    cout << "Controls: Use WSAD and the mouse to move around!" << endl;

    int redBits    = 8, greenBits = 8,    blueBits    = 8;
    int alphaBits  = 8, depthBits = 24,   stencilBits = 0;


    glfwInit();

    if(!glfwOpenWindow(windowWidth, windowHeight, redBits, greenBits, blueBits, alphaBits, depthBits, stencilBits, GLFW_WINDOW)) {
        cout << "Failed to open window!" << endl;
        glfwTerminate();
        return 0;
    }

    glfwSetMousePos(midWindowX, midWindowY);
    glfwDisable(GLFW_MOUSE_CURSOR); // Hide the mouse cursor

    // Change to the projection matrix, reset the matrix and set up our projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // The following code is a fancy bit of math that is eqivilant to calling:
    // gluPerspective(fieldOfView/2.0f, width/height , near, far);
    // We do it this way simply to avoid requiring glu.h
    GLfloat aspectRatio = (windowWidth > windowHeight)? float(windowWidth)/float(windowHeight) : float(windowHeight)/float(windowWidth);
    GLfloat fH = tan( float(fieldOfView / 360.0f * 3.14159f) ) * near;
    GLfloat fW = fH * aspectRatio;
    glFrustum(-fW, fW, -fH, fH, near, far);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glfwSetKeyCallback(handleKeypress);
    glfwSetMousePosCallback(handleMouseMove);

    while (!glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED)) {
        drawScene();
        moveCamera();
        checkGLError("Main loop");
    }

    glfwTerminate();

    return 0;
}
