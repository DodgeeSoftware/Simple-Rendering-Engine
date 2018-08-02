// include the standard input/output library
#include <iostream>
// include the string class
#include <string>
// include the openGL header
#include <gl/gl.h>
// include the openGL Utility header
#include <gl/glu.h>
// include the opengl extension header
#include <gl/glext.h>
// set a macro (required for mingw)
#define GLUT_DISABLE_ATEXIT_HACK
// include the OpenGL Utility Toolkit header
#include <glut.h>
// include soil library
#include <SOIL.h>
// include the utility class
#include "Utils.h"
// include the vector 2d class
#include "Vector2d.h"
// include the vector 3d class
#include "Vector3d.h"
// include the matrix4 class
#include "Matrix4.h"
// include the mesh factory
#include "MeshFactory.h"
// include the material class
#include "Material.h"
// include the scene manager
#include "SceneManager.h"
// include the mesh scene node
#include "MeshSceneNode.h"
// include the camera scene node
#include "CameraSceneNode.h";

// callbacks
void OnKeyDown(unsigned char key, int x, int y);
void OnKeyUp(unsigned char key, int x, int y);
void OnMouseMove(int x, int y);
void OnMouseClick(int button, int state, int x, int y);
void OnWindowResize(int width, int height);
void OnGamePad(unsigned int buttonMask, int x, int y, int z);
void OnMouseDrag(int x, int y);
void OnIdle();

// General application function
void init();
void loadContent();
void update();
void draw();
void handleEvents();
void freeResources();
void run();

// draw on screen display
void drawHeadsUpDisplay();
// process lighting
void doLighting();

// Controls
bool keys[256];
bool mouseButton[3];
Vector3d gamePadHat;
char gamePadButtonMask = 0;

float ambientLight1[] = {0.0f, 0.0f, 0.0f};
float diffuseLight1[] = {0.0f, 0.5f, 0.0f};
float specularLight1[] = {1.0f, 1.0f, 1.0f};
float lightPosition1[] = {-5.0f, -5.0f, 0.0f};
float lightDirection1[] = {0.0f, 0.0f, -1.0f};

float ambientLight2[] = {0.0f, 0.0f, 0.0f};
float diffuseLight2[] = {0.0f, 0.0f, 0.5f};
float specularLight2[] = {1.0f, 1.0f, 1.0f};
float lightPosition2[] = {5.0f, 5.0f, 0.0f};
float lightDirection2[] = {0.0f, 0.0f, -1.0f};

SceneManager sceneManager;

MeshFactory meshFactory;

// Declare some textures
GLuint testTexture = 0;
GLuint skydome = 0;
GLuint ringTexture = 0;
GLuint dodgeeSoftwareLogo = 0;

int w = 800;
int h = 600;

float degree = 0.0f;
float scale = 1.0f;

bool headsUpDisplay = true;

void setOrthographicProjection() {

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);
	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();
	// reset matrix
	glLoadIdentity();
	// set a 2D orthographic projection
	gluOrtho2D(0, w, 0, h);
	// invert the y axis, down is positive
	glScalef(1, -1, 1);
	// mover the origin from the bottom left corner
	// to the upper left corner
	glTranslatef(0, -h, 0);
	// switch to moel view projection mode
	glMatrixMode(GL_MODELVIEW);
}

void resetPerspectiveProjection()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void renderSpacedBitmapString(float x, float y, int spacing, void* font, char* string)
{
    char *c;
    int x1=(int)x;
    for (c=string; *c != '\0'; c++)
    {
        glRasterPos2f(x1,y);
        glutBitmapCharacter(font, *c);
        x1 = x1 + glutBitmapWidth(font,*c) + spacing;
    }
}

void renderVerticalBitmapString(float x, float y, int bitmapHeight, void* font, char* string)
{
    char *c;
    int i;
    for (c=string,i=0; *c != '\0'; i++,c++)
    {
        glRasterPos2f(x, y+bitmapHeight*i);
        glutBitmapCharacter(font, *c);
    }
}

void renderBitmapString(float x, float y, float z, void* font, char* string)
{
    char *c;
    glRasterPos3f(x, y,z);
    for (c=string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

int main(int argcp, char **argv)
{
    // initialise glut
    glutInit(&argcp, argv);
    // initialise the app
    init();
    // load content
    loadContent();
    // call the main loop
    glutMainLoop();
}

void init()
{
    for(unsigned int i = 0; i < 256; i++)
        keys[i] = false;

    for(unsigned int i=0; i < 3; i++)
        mouseButton[i] = GLUT_UP;

    // setup the glut display mode
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

//    // REDDUNDANT
//    // set the position  of the application window
//    glutInitWindowPosition(0, 0);
//    // set the width and height of the application window
//    glutInitWindowSize(1024, 768);
//    // create the application window
//    glutCreateWindow("Assignment 2: Group 30");
//    // fullscreen the window
//    glutFullScreen();
//    // turn off the cursor
//    glutSetCursor(GLUT_CURSOR_NONE);

    // 640x480, 16bit pixel depth, 60Hz refresh rate
    glutGameModeString( "800x600:24@60" );
    // enter game mode
    glutEnterGameMode();
    // register the display function callback
    glutDisplayFunc( run );
    // register the idle function callback
    glutIdleFunc( run );
    // register the reshape function
    glutReshapeFunc( OnWindowResize );
    // register the keydown callback
    glutKeyboardFunc( OnKeyDown );
    // register the keyup callback
    glutKeyboardUpFunc( OnKeyUp );
    // register the mouse motion callback
    glutMotionFunc( OnMouseDrag );
    // register the mouse button callback
    glutMouseFunc( OnMouseClick );
    // register the mouse passive motion callback
    glutPassiveMotionFunc( OnMouseMove );
    // register the joystick callback
    glutJoystickFunc(OnGamePad, 10);
    // switch off key repeat
    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    // enable smooth shading
    glEnable(GL_SMOOTH);
    // enable depth testing
    glEnable(GL_DEPTH_TEST);
    // set line width
    glLineWidth( 1.0f );
    // enable gl lighing
    glEnable(GL_LIGHTING);
    // turn on coloured materials
    glEnable(GL_COLOR_MATERIAL);
    // enable textures
    glEnable(GL_TEXTURE_2D);
    // enable smooth shading
    glEnable(GL_SMOOTH);
//    // enable opengl culling
//    glEnable(GL_CULL_FACE);
//    // cull on counter clockwise verticies
//    glFrontFace(GL_CCW);
    // setup an opengl light
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glutSetCursor(GLUT_CURSOR_NONE);


    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

}

void loadContent()
{
    // TODO - Replace with an xml scene builder

    // load an image file directly as a new OpenGL texture
    testTexture = SOIL_load_OGL_texture
    (
        "media/texture.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    if (testTexture == 0)
        exit(0);


    // load an image file directly as a new OpenGL texture
    skydome = SOIL_load_OGL_texture
    (
        "media/sky.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    ringTexture = SOIL_load_OGL_texture
    (
        "media/skygold.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    if (skydome == 0)
        exit(0);

    // load an image file directly as a new OpenGL texture
    dodgeeSoftwareLogo = SOIL_load_OGL_texture
    (
        "media/DodgeeSoft.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    if (dodgeeSoftwareLogo == 0)
        exit(0);

    CameraSceneNode* camera = new CameraSceneNode(&sceneManager);
    camera->setPosition(Vector3d(0.0f, 0.0f, 100.0f));
    camera->setRotationDegrees(Vector3d(0.0f, -90.0f, 0.0f));
    sceneManager.addCameraSceneNode( camera, "camera1" );
    sceneManager.setCurrentCamera( "camera1" );

    Material material;
    material.setAmbient(1.0f, 1.0f, 1.0f, 1.0f);
    material.setSpecular(0.5f, 0.5f, 0.5f, 0.0f);
    material.setDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
    material.setEmission(0.0f, 0.0f, 0.0f, 0.0f);
    material.setShininess(0.0f);
    material.setTexture(skydome);

    MeshSceneNode* skyDome = new MeshSceneNode(&sceneManager);
    skyDome->setMesh( meshFactory.createSphere(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(0.0f, 0.0f, 0.0f), Vector3d(1000.0f, 1000.0f, 1000.0f)) );
    material.setWireframeFlag(false);
    material.setNormalsFlag(false);
    material.setEnvironmentMapFlag(false);
    material.setTexture(skydome);
    skyDome->setMaterial(material);
    sceneManager.setCurrentSky(skyDome);

    material.setNormalsFlag(false);
    material.setWireframeFlag(false);
    material.setEnvironmentMapFlag(false);
    material.setNormalsFlag(false);
    material.setTexture(testTexture);

    MeshSceneNode* mesh = new MeshSceneNode(&sceneManager);
    mesh->setMesh( meshFactory.createCube(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(0.0f, 0.0f, 0.0f), Vector3d(100.0f, 1.0f, 100.0f) ) );
    mesh->setMaterial(material);
    mesh->setPosition(Vector3d(0.0f, -25.0f, 0.0f) );
    sceneManager.addMeshSceneNode(mesh, "mesh");

    material.setTexture(skydome);
    material.setEnvironmentMapFlag(true);
    MeshSceneNode* mesh2 = new MeshSceneNode(&sceneManager);
    mesh2->setMesh( meshFactory.createCube(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(0.0f, 0.0f, 0.0f), Vector3d(50.0f, 1.0f, 50.0f) ) );
    mesh2->setMaterial(material);
    mesh2->setPosition(Vector3d(0.0f, 25.0f, 0.0f) );
    sceneManager.addMeshSceneNode(mesh2, "mesh2");

    MeshSceneNode* mesh3 = new MeshSceneNode(&sceneManager);
    mesh3->setMesh( meshFactory.createSquareBasedPyramid(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(0.0f, 45.0f, 0.0f), Vector3d(1.0f, 1.0f, 1.0f), 142.5f, 100.0f ) );
    mesh3->setMaterial(material);
    mesh3->setPosition(Vector3d(0.0f, 75.0f, 0.0f) );
//    mesh3->setRotationDegrees(Vector3d(0.0f, 45.0f,0.0f));
    sceneManager.addMeshSceneNode(mesh3, "mesh3");

    Vector3d vecs[6] = {Vector3d(40.0f,0.0f,40.0f),Vector3d(40.0f,0.0f,0.0f),Vector3d(-40.0f,0.0f,40.0f),Vector3d(40.0f,0.0f,-40.0f),Vector3d(-40.0f,0.0f,-40.0f),Vector3d(-40.0f,0.0f,0.0f)};
    for ( int x = 0 ; x < 6 ; x++ )
    {
        char buffer[64];
        snprintf(buffer, 64, "pylon%d", x);
        MeshSceneNode* pylon = new MeshSceneNode(&sceneManager);
        pylon->setMesh( meshFactory.createCylinder(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(0.0f, 0.0f, 0.0f), Vector3d(1.0f, 1.0f, 1.0f), 50.0f, Vector2d(5.0f, 5.0f) ) );
        pylon->setMaterial(material);
        pylon->setPosition(vecs[x]);
        sceneManager.addMeshSceneNode(pylon, buffer);
    }

    for ( int x = 0 ; x < 4 ; x++ )
    {
        char buffer[64];
        snprintf(buffer, 64, "base%d", x);
        Vector3d vec = Vector3d(-15.0f, -24.0f, -20.0f);
        vec.x += (10.0*x);
        MeshSceneNode* base = new MeshSceneNode(&sceneManager);
        base->setMesh( meshFactory.createCube(vec, Vector3d(0.0f,0.0f,0.0f), Vector3d(3.0f,0.5f,3.0f)));
        base->setMaterial(material);
        sceneManager.addMeshSceneNode(base, buffer);

        snprintf(buffer, 64, "base2%d", x);
        MeshSceneNode* base2 = new MeshSceneNode(&sceneManager);
        base2->setMesh( meshFactory.createCube(vec+Vector3d(0.0f,0.5f,0.0f), Vector3d(0.0f,0.0f,0.0f), Vector3d(2.0f,0.5f,2.0f)));
        base2->setMaterial(material);
        sceneManager.addMeshSceneNode(base2, buffer);

        snprintf(buffer, 64, "lilpillar%d", x);
        MeshSceneNode* lilpillar = new MeshSceneNode(&sceneManager);
        lilpillar->setMesh( meshFactory.createCylinder(vec+Vector3d(0.0f,4.0f,0.0f), Vector3d(0.0f,0.0f,0.0f), Vector3d(1.0f,1.0f,1.0f), 6.0f, Vector2d(1.0f,1.0f)));
        lilpillar->setMaterial(material);
        sceneManager.addMeshSceneNode(lilpillar, buffer);

        snprintf(buffer, 64, "lilplat%d", x);
        MeshSceneNode* lilplat = new MeshSceneNode(&sceneManager);
        lilplat->setMesh( meshFactory.createSquareBasedPyramid(vec+Vector3d(0.0f,6.0f,0.0f), Vector3d(180.0f,45.0f,0.0f), Vector3d(1.0f,1.0f,1.0f), 8.0f, 4.0f));
        lilplat->setMaterial(material);
        sceneManager.addMeshSceneNode(lilplat, buffer);
    }

    material.setTexture(ringTexture);
    Vector3d pos = Vector3d(-15.0f, -10.0f, -20.0f);

    MeshSceneNode* rotate = new MeshSceneNode(&sceneManager);
    rotate->setMesh( meshFactory.createTorus(Vector3d(0.0f,0.0f,0.0f), Vector3d(0.0f,0.0f,0.0f), Vector3d(0.5f,0.5f,0.5f) ) );
    rotate->setPosition(pos);
    rotate->setMaterial(material);
    sceneManager.addMeshSceneNode(rotate, "rotate");

    pos+=Vector3d(10.0f,0.0f,0.0f);
    MeshSceneNode* scale = new MeshSceneNode(&sceneManager);
    scale->setMesh( meshFactory.createHollowCylinder(Vector3d(0.0f,0.0f,0.0f), Vector3d(90.0f,0.0f,0.0f), Vector3d(2.0f,2.0f,2.0f) ) );
    scale->setPosition(pos);
    scale->setMaterial(material);
    sceneManager.addMeshSceneNode(scale, "scale");

    pos+=Vector3d(10.0f,0.0f,0.0f);
    MeshSceneNode* translate = new MeshSceneNode(&sceneManager);
    translate->setMesh( meshFactory.createSphere(Vector3d(0.0f,0.0f,0.0f), Vector3d(0.0f,0.0f,0.0f), Vector3d(2.0f,2.0f,2.0f) ) );
    translate->setPosition(pos);
    translate->setMaterial(material);
    sceneManager.addMeshSceneNode(translate, "translate");

    pos+=Vector3d(10.0f,0.0f,0.0f);
    MeshSceneNode* all = new MeshSceneNode(&sceneManager);
    all->setMesh( meshFactory.createSphere(Vector3d(0.0f,0.0f,0.0f), Vector3d(0.0f,0.0f,0.0f), Vector3d(2.0f,2.0f,2.0f) ) );
    all->setPosition(pos);
    material.setWireframeFlag(true);
    all->setMaterial(material);
    sceneManager.addMeshSceneNode(all, "all");

    glutWarpPointer(1024/2, 768/2);
}

void handleEvents()
{
    if (keys[27] == true)
    {
        glutLeaveGameMode();
        freeResources();
        exit(0);
    }

    CameraSceneNode* cameraSceneNode = sceneManager.getCurrentCamera();

    if (keys['W'] == true || keys['w'] == true)
    {
        cameraSceneNode->setStride(cameraSceneNode->getStride() + 0.1f);
    }
    if (keys['S'] == true || keys['s'] == true)
    {
        cameraSceneNode->setStride(cameraSceneNode->getStride() - 0.1f);
    }

    if (keys['A'] == true || keys['a'] == true)
    {
        cameraSceneNode->setStrafe(cameraSceneNode->getStrafe() - 0.1f);
    }

    if (keys['D'] == true || keys['d'] == true)
    {
        cameraSceneNode->setStrafe(cameraSceneNode->getStrafe() + 0.1f);
    }

    if (keys['P'] == true || keys['p'] == true)
    {
        sceneManager.saveScreenShot();
    }
}

void update()
{
    CameraSceneNode* cameraSceneNode = sceneManager.getCurrentCamera();
    cameraSceneNode->setStrafe(cameraSceneNode->getStrafe() + gamePadHat.x);
    cameraSceneNode->setStride(cameraSceneNode->getStride()- gamePadHat.y);
    cameraSceneNode->setRotationDegrees( cameraSceneNode->getRotationDegrees()  + Vector3d(0.0f, -gamePadHat.z*10.0f, 0.0f));

    sceneManager.update();

    degree += 36.0f;
    scale += 1.0f;

    sceneManager.getMeshSceneNode("rotate")->setRotationDegrees(Vector3d(degree, degree, 0.0f));
    sceneManager.getMeshSceneNode("scale")->setScale(Vector3d(fabs(cos(scale*DEG2RAD))+1.0f,fabs(cos(scale*DEG2RAD))+1.0f,fabs(cos(scale*DEG2RAD)+1.0f)));
    sceneManager.getMeshSceneNode("translate")->setPosition(Vector3d(5.0f, -10.0f + cos(degree*DEG2RAD/2)*2.0f, -20.0f));

    glutWarpPointer(1024/2, 768/2);
}

void draw()
{
    // clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // alter the world matrix to create a perspective
//    cameraSceneNode.draw();

    sceneManager.draw();

    // draw the hud
    if (headsUpDisplay == true)
        drawHeadsUpDisplay();

    // process lighting
    doLighting();

    // page flip
    glutSwapBuffers();
}

void freeResources()
{
    sceneManager.freeResources();
}

void OnIdle()
{

}

void run()
{
    handleEvents();
    update();
    draw();
}

void OnKeyDown(unsigned char ascii, int x, int y)
{
    keys[ascii] = true;
}

void OnKeyUp(unsigned char ascii, int x, int y)
{
    keys[ascii] = false;
}

void OnMouseClick(int button, int state, int x, int y)
{
    mouseButton[button] = state;
}

void OnMouseDrag(int x, int y)
{

}

void OnMouseMove(int x, int y)
{
    if (x>0 && x <1024 && y>0 && y <768)
    {
        CameraSceneNode* cameraSceneNode = sceneManager.getCurrentCamera();

        Vector2d deltaMousePosition = Vector2d(1024.0f/2.0f-x, y-768.0f/2.0f);
        //deltaMousePosition.normalise();

        deltaMousePosition = (deltaMousePosition) * 0.00005f;


        cameraSceneNode->setOmega(cameraSceneNode->getOmega() + Vector3d(-deltaMousePosition.y, -deltaMousePosition.x, 0.0f) );

    }
}

void OnWindowResize(int width, int height)
{
	// determine aspect ratio
	float ratio = (float)width / (float)height;
	// Select the projection matrix
	glMatrixMode(GL_PROJECTION);
	// reset current matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, width, height);
	 // setup the field of view in degrees
	float fieldOfView = 45;
	// setup the near plane in pixels
	float near = 1.0f;
	// setup the far plane in pixels
	float far = 2000.0f;
	// Set the correct perspective.
	gluPerspective(fieldOfView, ratio, near, far);
}

void OnGamePad(unsigned int buttonMask, int x, int y, int z)
{
    gamePadButtonMask = buttonMask;
    gamePadHat = (Vector3d(x,y,z).magnitude()> 500.0f) ? Vector3d(x,y,z).normalised()*0.1f: Vector3d(0.0f,0.0f,0.0f);
}


void drawHeadsUpDisplay()
{
    setOrthographicProjection();
        glPushMatrix();
            glLoadIdentity();
            glDisable(GL_LIGHTING);

            glDisable(GL_DEPTH_TEST);
                glColor3f(0.0f, 0.0f, 0.0f);
                glRectd(0,0,w, 100);
                glRectd(0,h-100,w, h);
            glEnable(GL_DEPTH_TEST);

            glColor3f(1.0f, 1.0f, 1.0f);
            renderBitmapString(0, 18.0f*1.0f,0, GLUT_BITMAP_TIMES_ROMAN_24,"Group 30");
            renderBitmapString(0, 18.0f*2.0f,0, GLUT_BITMAP_TIMES_ROMAN_24,"11058827 - Shem Taylor");
            renderBitmapString(0, 18.0f*3.0f,0, GLUT_BITMAP_TIMES_ROMAN_24,"11058839 - Shaun Ware");

            glBindTexture(GL_TEXTURE_2D, dodgeeSoftwareLogo);
            glBegin(GL_QUADS);
                glTexCoord2d(0.0f, 1.0f);
                glVertex2d(w-100, h-90);
                glTexCoord2d(1.0f, 1.0f);
                glVertex2d(w-20, h-90);
                glTexCoord2d(1.0f, 0.0f);
                glVertex2d(w-20, h-10);
                glTexCoord2d(0.0f, 0.0f);
                glVertex2d(w-100, h-10);
            glEnd();

            glEnable(GL_LIGHTING);
        glPopMatrix();
    resetPerspectiveProjection();
}

void doLighting()
{
    glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, 0.0f);
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight1);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight1);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight1);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition1);
//        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDirection1);
//        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0f);
//        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 10.0f);

        glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight2);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight2);
        glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight2);
        glLightfv(GL_LIGHT1, GL_POSITION, lightPosition2);
    glPopMatrix();
}
