#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <string>
#include <map>

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

#include "ISceneNode.h"
#include "CameraSceneNode.h"

class SceneManager
{
public:
    SceneManager() {skySceneNode = NULL; currentCamera = NULL;}
    virtual ~SceneManager() {}

    // add a light scene node to the scene manager
    void addLightSceneNode(ISceneNode* node, std::string name);
    // add a camera scene node to the scene manager
    void addCameraSceneNode(CameraSceneNode* node, std::string name);
    // add a mesh scene node to the scene manager
    void addMeshSceneNode(ISceneNode* node, std::string name);

    // get a light scene node
    ISceneNode* getLightSceneNode(std::string name);
    // get a camera scene node
    ISceneNode* getCameraSceneNode(std::string name);
    // get a mesh scene node
    ISceneNode* getMeshSceneNode(std::string name);

    // set current sky
    void setCurrentSky( ISceneNode* skySceneNode ) { this->skySceneNode = skySceneNode; }

    // set the current camera
    void setCurrentCamera(std::string name);
    // get the current camera
    CameraSceneNode* getCurrentCamera();

    // function to take screenshot
    bool saveScreenShot();

    // update the scene manager
    void update();

    // draw the scene manager
    void draw();

    // free resources used and clean up the scene manager
    void freeResources();

private:
    // stl container for light scene nodes
    std::map<std::string, ISceneNode*> lightSceneNodes;
    // stl container for camera scene nodes
    std::map<std::string, CameraSceneNode*> cameraSceneNodes;
    // stl container for mesh scene nodes
    std::map<std::string, ISceneNode*> meshSceneNodes;

    // a pointer to the current scene node
    ISceneNode* skySceneNode;
    // a pointer to the current camera
    CameraSceneNode* currentCamera;
};

#endif // SCENEMANAGER_H
