#include <iostream>
 
#include <GL/GLee.h>         // No need to link to GL/gl.h
#include <GL/glfw.h>      // Include OpenGL Framework library
#include <GL/freeglut.h>  // Include FreeGLUT so we can easily draw spheres and calculate our viewing frustrum
#include <math.h>         // Used only for sin() and cos() functions
 
using namespace std;
 
const float TO_RADS = 3.141592654f / 180.0f; // The value of 1 degree in radians
 
GLint windowWidth  = 800;                    // Width of our window
GLint windowHeight = 600;                    // Heightof our window
 
GLint midWindowX = windowWidth  / 2;         // Middle of the window horizontally
GLint midWindowY = windowHeight / 2;         // Middle of the window vertically
 
GLfloat fieldOfView = 45.0f;                 // Define our field of view (i.e. how quickly foreshortening occurs)
GLfloat near        = 1.0f;                  // The near (Z Axis) point of our viewing frustrum (default 1.0f)
GLfloat far         = 1500.0f;               // The far  (Z Axis) point of our viewing frustrum (default 1500.0f)
 
// Camera rotation
GLfloat camXRot = 0.0f;
GLfloat camYRot = 0.0f;
GLfloat camZRot = 0.0f;
 
// Camera position
GLfloat camXPos = 0.0f;
GLfloat camYPos = 0.0f;
GLfloat camZPos = 0.0f;
 
// Camera movement speed
GLfloat camXSpeed = 0.0f;
GLfloat camYSpeed = 0.0f;
GLfloat camZSpeed = 0.0f;
 
GLint frameCount = 0; // How many frames have we drawn?
 
// Location of the sun (i.e. how far deep into the screen is it?)
GLfloat sunZLocation = -300.0f;
 
// How many segments make up our sphere around the latutude and longitude of the sphere
// The higher the number, the closer an approximation to a sphere we get! Try low numbers to see how bad it looks!
int sphereLatitudalSegments  = 100;
int sphereLongitudalSegments = 100;
 
// "Earth" details
GLbyte earthColour[]       = { 0, 0, 255 };
GLfloat earthOrbitDistance = 100.0f;
GLfloat earthOrbitSpeed    = 0.5f;
GLfloat earthRot           = 0.0f;
 
// "Moon" details
GLbyte moonColour[]        = { 255, 0, 0 };
GLfloat moonOrbitDistance  = 30.0f;
GLfloat moonOrbitSpeed     = 1.5f;
GLfloat moonRot            = 0.0f;
 
// Set the light source location to be the same as the sun position
// Don't forget that the position is a FOUR COMPONENT VECTOR (with the last component as w) if you omit the last component expect to get NO LIGHT!!!
// Learnt that one the hard way... =P
GLfloat  lightPos[] = { 0.0f, 0.0f, -300.0f, 1.0f };
 
GLfloat movementSpeedFactor = 3.0f;
 
bool holdingForward     = false;
bool holdingBackward    = false;
bool holdingLeftStrafe  = false;
bool holdingRightStrafe = false;
 
float toRads(const float &theAngleInDegrees)
{
    return theAngleInDegrees * TO_RADS;
}
 
void checkGLError(const char * errorLocation)
{
    unsigned int gle = glGetError();
 
    if (gle != GL_NO_ERROR)
    {
        cerr << "GL Error discovered from caller " << errorLocation << ": " << gle << endl;
        exit(1);
    }
 
}
 
void initGL()
{
    // ----- GLFW Settings -----
 
    glfwDisable(GLFW_MOUSE_CURSOR); // Hide the mouse cursor
 
    // ----- Window and Projection Settings -----
 
    // Set the window title
    glfwSetWindowTitle("Solar System FPS Controls | r3dux.org");
 
    // Setup our viewport to be the entire size of the window
    glViewport(0, 0, (GLsizei)windowWidth, (GLsizei)windowHeight);
 
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
 
    // ----- OpenGL settings -----
 
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set out clear colour to black, full alpha
 
    glfwSwapInterval(1);        // Lock to vertical sync of monitor (normally 60Hz, so 60fps)
 
    glShadeModel(GL_SMOOTH);    // Enable (gouraud) shading
 
    glEnable(GL_DEPTH_TEST);    // Enable depth testing
 
    glClearDepth(1.0f);         // Clear the entire depth of the depth buffer
 
    glDepthFunc(GL_LEQUAL);		// Set our depth function to overwrite if new value less than or equal to current value
 
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Ask for nicest perspective correction
 
    glEnable(GL_CULL_FACE); // Do not draw polygons facing away from us
 
    glLineWidth(2.0f);			// Set a 'chunky' line width
 
    // ---- Set up OpenGL lighting -----
 
    // Enable lighting
    glEnable(GL_LIGHTING);
 
    // Ambient, diffuse and specular lighting values (note that these are ALL FOUR COMPONENT VECTORS!)
    GLfloat  ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
 
    GLint specularMagnitude = 64; // Define how "tight" our specular highlights are (larger number = smaller specular highlight). The valid range is is 1 to 128
 
    // Setup and enable light 0
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);          // Specify the position of the light
    glLightfv(GL_LIGHT0, GL_AMBIENT,  ambientLight);      // Specify ambient light properties
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffuseLight);      // Specify diffuse light properties
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);     // Specify specular light properties
    glEnable(GL_LIGHT0);
 
    // Enable colour tracking of materials
    glEnable(GL_COLOR_MATERIAL);
 
    // Define the shininess of the material we'll use to draw things
    GLfloat materialSpecularReflectance[] = { 1.0f, 1.0f, 1.0f, 1.0f };
 
    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
 
    // Use our shiny material and magnitude
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecularReflectance);
    glMateriali(GL_FRONT, GL_SHININESS, specularMagnitude);
 
    // Check for any OpenGL errors (providing the location we called the function from)
    checkGLError("InitGL");
}
 
// Function to move the camera the amount we've calculated in the calculateCameraMovement function
void moveCamera()
{
    camXPos += camXSpeed;
    camYPos += camYSpeed;
    camZPos += camZSpeed;
}
 
// Function to deal with mouse position changes, called whenever the mouse cursorm moves
void handleMouseMove(int mouseX, int mouseY)
{
    GLfloat vertMouseSensitivity  = 10.0f;
    GLfloat horizMouseSensitivity = 10.0f;
 
    //cout << "Mouse cursor is at position (" << mouseX << ", " << mouseY << endl;
 
    int horizMovement = mouseX - midWindowX;
    int vertMovement  = mouseY - midWindowY;
 
    camXRot += vertMovement / vertMouseSensitivity;
    camYRot += horizMovement / horizMouseSensitivity;
 
    // Control looking up and down with the mouse forward/back movement
    // Limit loking up to vertically up
    if (camXRot < -90.0f)
    {
        camXRot = -90.0f;
    }
 
    // Limit looking down to vertically down
    if (camXRot > 90.0f)
    {
        camXRot = 90.0f;
    }
 
    // Looking left and right. Keep the angles in the range -180.0f (anticlockwise turn looking behind) to 180.0f (clockwise turn looking behind)
    if (camYRot < -180.0f)
    {
        camYRot += 360.0f;
    }
 
    if (camYRot > 180.0f)
    {
        camYRot -= 360.0f;
    }
 
    // Reset the mouse position to the centre of the window each frame
    glfwSetMousePos(midWindowX, midWindowY);
}
 
// Function to calculate which direction we need to move the camera and by what amount
void calculateCameraMovement()
{
    // Break up our movement into components along the X, Y and Z axis
    float camMovementXComponent = 0.0f;
    float camMovementYComponent = 0.0f;
    float camMovementZComponent = 0.0f;
 
    if (holdingForward == true)
    {
        // Control X-Axis movement
        float pitchFactor = cos(toRads(camXRot));
        camMovementXComponent += ( movementSpeedFactor * float(sin(toRads(camYRot))) ) * pitchFactor;
 
        // Control Y-Axis movement
        camMovementYComponent += movementSpeedFactor * float(sin(toRads(camXRot))) * -1.0f;
 
        // Control Z-Axis movement
        float yawFactor = float(cos(toRads(camXRot)));
        camMovementZComponent += ( movementSpeedFactor * float(cos(toRads(camYRot))) * -1.0f ) * yawFactor;
    }
 
    if (holdingBackward == true)
    {
        // Control X-Axis movement
        float pitchFactor = cos(toRads(camXRot));
        camMovementXComponent += ( movementSpeedFactor * float(sin(toRads(camYRot))) * -1.0f) * pitchFactor;
 
        // Control Y-Axis movement
        camMovementYComponent += movementSpeedFactor * float(sin(toRads(camXRot)));
 
        // Control Z-Axis movement
        float yawFactor = float(cos(toRads(camXRot)));
        camMovementZComponent += ( movementSpeedFactor * float(cos(toRads(camYRot))) ) * yawFactor;
    }
 
    if (holdingLeftStrafe == true)
    {
        // Calculate our Y-Axis rotation in radians once here because we use it twice
        float yRotRad = toRads(camYRot);
 
        camMovementXComponent += -movementSpeedFactor * float(cos(yRotRad));
        camMovementZComponent += -movementSpeedFactor * float(sin(yRotRad));
    }
 
    if (holdingRightStrafe == true)
    {
        // Calculate our Y-Axis rotation in radians once here because we use it twice
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
    {
        //cout << "high capping X speed to: " << movementSpeedFactor << endl;
        camXSpeed = movementSpeedFactor;
    }
    if (camXSpeed < -movementSpeedFactor)
    {
        //cout << "low capping X speed to: " << movementSpeedFactor << endl;
        camXSpeed = -movementSpeedFactor;
    }
 
    // Y Speed cap
    if (camYSpeed > movementSpeedFactor)
    {
        //cout << "low capping Y speed to: " << movementSpeedFactor << endl;
        camYSpeed = movementSpeedFactor;
    }
    if (camYSpeed < -movementSpeedFactor)
    {
        //cout << "high capping Y speed to: " << movementSpeedFactor << endl;
        camYSpeed = -movementSpeedFactor;
    }
 
    // Z Speed cap
    if (camZSpeed > movementSpeedFactor)
    {
        //cout << "high capping Z speed to: " << movementSpeedFactor << endl;
        camZSpeed = movementSpeedFactor;
    }
    if (camZSpeed < -movementSpeedFactor)
    {
        //cout << "low capping Z speed to: " << movementSpeedFactor << endl;
        camZSpeed = -movementSpeedFactor;
    }
}
 
// Function to set flags according to which keys are pressed or released
void handleKeypress(int theKey, int theAction)
{
    // If a key is pressed, toggle the relevant key-press flag
    if (theAction == GLFW_PRESS)
    {
 
        switch(theKey)
        {
        case 'W':
            holdingForward = true;
            break;
 
        case 'S':
            holdingBackward = true;
            break;
 
        case 'A':
            holdingLeftStrafe = true;
            break;
 
        case 'D':
            holdingRightStrafe = true;
            break;
 
        default:
            // Do nothing...
            break;
        }
    }
    else // If a key is released, toggle the relevant key-release flag
    {
        switch(theKey)
        {
        case 'W':
            holdingForward = false;
            break;
 
        case 'S':
            holdingBackward = false;
            break;
 
        case 'A':
            holdingLeftStrafe = false;
            break;
 
        case 'D':
            holdingRightStrafe = false;
            break;
 
        default:
            // Do nothing...
            break;
        }
    }
}
 
// Function to draw a grid of lines
void drawGround()
{
    GLfloat extent      = 600.0f; // How far on the Z-Axis and X-Axis the ground extends
    GLfloat stepSize    = 20.0f;  // The size of the separation between points
    GLfloat groundLevel = -50.0f;   // Where on the Y-Axis the ground is drawn
 
    // Set colour to white
    glColor3ub(255, 255, 255);
 
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
 
}
 
// Function to draw our spheres and position the light source
void drawScene()
{
    // Clear the screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    // Reset the matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
 
    // Move the camera to our location in space
    glRotatef(camXRot, 1.0f, 0.0f, 0.0f);        // Rotate our camera on the x-axis (looking up and down)
    glRotatef(camYRot, 0.0f, 1.0f, 0.0f);        // Rotate our camera on the  y-axis (looking left and right)
    glTranslatef(-camXPos,-camYPos,-camZPos);    // Translate the modelviewm matrix to the position of our camera
 
    // Draw the lower ground-grid
    drawGround();
 
    // Draw the upper ground-grid, keeping a copy of our current matrix on the stack before we translate it
    glPushMatrix();
 
    glTranslatef(0.0f, 200.0f, 0.0f);
 
    drawGround();
 
    glPopMatrix();
 
    // Move everything "into" the screen (i.e. move 300 units along the Z-axis into the screen) so that all positions are now relative to the location of the sun
    glTranslatef(0.0f, 0.0f, sunZLocation);
 
    // Define our light position
    // *** IMPORTANT! *** A light position takes a FOUR component vector! The last component is w! If you leave off the last component, you get NO LIGHT!!!
    GLfloat newLightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
 
    glLightfv(GL_LIGHT0, GL_POSITION, newLightPos);  // Place the light where the sun is!
 
    // Rotate the coordinate system around the y-axis and then translate to shift outwards
    glRotatef(earthRot, 0.0f, 1.0f, 0.0f);
    glTranslatef(earthOrbitDistance, 0.0f, 0.0f);
 
 
    glfwSwapBuffers(); // Swap the buffers to display the scene (so we don't have to watch it being drawn!)
}
 
// Fire it up...
int main(int argc, char **argv)
{
    cout << "Controls: Use WSAD and the mouse to move around!" << endl;
 
    // Frame counter and window settings variables
    int	redBits    = 8, greenBits = 8,    blueBits    = 8;
    int alphaBits  = 8, depthBits = 24,   stencilBits = 0;
 
    // Flag to keep our main loop running
    bool running = true;
 
    // ----- Intialiase FreeGLUT -----
 
    // Note: We're only using freeGLUT to draw some spheres, so if you modify the code to not include any calls
    // to glutSolidSphere, then you don't need this, the header or the lib...
    glutInit(&argc, argv);
 
    // Initialise GLFW
    glfwInit();
 
    // Ask for 4x AntiAliasing (this doesn't mean we'll get it - it'll work only if the GLX_ARB_multisample extension is available)
    // Note: Hints must be provided BEFORE the window is opened! But we can't query for it with GLEE until the window is opened! Catch 22!
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
 
    // Create a window
    if(!glfwOpenWindow(windowWidth, windowHeight, redBits, greenBits, blueBits, alphaBits, depthBits, stencilBits, GLFW_WINDOW))
    {
        cout << "Failed to open window!" << endl;
        glfwTerminate();
        return 0;
    }
 
    // ----- Initialise GLEE -----
 
    // Initialise GLee once we've got a rendering context
    // Note: We don't really have to do this because it's called automatically, but if we do it - we KNOW it's been called!
    GLeeInit();
 
    // Check for the OpenGL extension which allows us to use vsync
    if (GLEE_GLX_SGI_swap_control)
    {
        cout << "Extension found: GLX_SGI_swap_control (vsync can be used)." << endl;
        glfwSwapInterval(1);
    }
    else
    {
        cout << "Extension NOT found: GLX_SGI_swap_control (vsync cannot be used)." << endl;
        glfwSwapInterval(0);
    }
 
    // Check for the OpenGL extension which allows us to use antialiasing
    if (GLEE_ARB_multitexture)
    {
        cout << "Extension found: GLX_ARB_multitexture (anti-aliasing can be used)." << endl;
 
        // If the extension's available, we likely got anti-aliasing, so disable line smoothing as it comes free with the AA
        glDisable(GL_LINE_SMOOTH);
    }
    else
    {
        cout << "Extension NOT found: GLX_ARB_multitexture (anti-aliasing cannot be used)." << endl;
 
        // If the extention's not available, turn on line smoothing
        glEnable(GL_LINE_SMOOTH);
    }
 
    // Set the mouse cursor to the centre of our window
    glfwSetMousePos(midWindowX, midWindowY);
 
    // Call our initGL function to set up our OpenGL options
    initGL();
 
    // Specify the function which should execute when a key is pressed or released
    glfwSetKeyCallback(handleKeypress);
 
    // Specify the function which should execute when the mouse is moved
    glfwSetMousePosCallback(handleMouseMove);
 
    while (running == true)
    {
        // Draw our scene
        drawScene();
 
        // Calculate our camera movement
        calculateCameraMovement();
 
        // Move our camera
        moveCamera();
 
        // Increase our frame counter
        frameCount++;
 
        // Check for any OpenGL errors (providing the location we called the function from)
        checkGLError("Main loop");
 
        // exit if ESC was pressed or window was closed
        running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
    }
 
    // Clean up GLFW and exit
    glfwTerminate();
 
    return 0;
}
