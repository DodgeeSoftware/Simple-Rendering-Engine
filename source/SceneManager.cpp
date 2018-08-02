#include "SceneManager.h"

void SceneManager::addLightSceneNode(ISceneNode* node, std::string name)
{
    // if the new node does not equal null
    if ( node != NULL )
    {
        // if there is not already a node by this name
        if ( lightSceneNodes.find(name) == lightSceneNodes.end() )
        {
            // add the scene node to the map
            lightSceneNodes[name] = node;
        }
    }
}

void SceneManager::addCameraSceneNode(CameraSceneNode* node, std::string name)
{
    // if the new node does not equal null
    if ( node != NULL )
    {
        // if there is not already a node by this name
        if ( cameraSceneNodes.find(name) == cameraSceneNodes.end() )
        {
            // add the scene node to the map
            cameraSceneNodes[name] = node;
        }
    }
}

void SceneManager::addMeshSceneNode(ISceneNode* node, std::string name)
{
    // if the new node does not equal null
    if ( node != NULL )
    {
        // if there is not already a node by this name
        if ( meshSceneNodes.find(name) == meshSceneNodes.end() )
        {
            // add the scene node to the map
            meshSceneNodes[name] = node;
        }
    }
}

ISceneNode* SceneManager::getLightSceneNode(std::string name)
{
    // if there is a registered node by this name
    if ( lightSceneNodes.find(name) != lightSceneNodes.end() )
    {
        // return the found node
        return lightSceneNodes[name];
    }
    // if no node found, return null
    return NULL;
}

ISceneNode* SceneManager::getCameraSceneNode(std::string name)
{
    // if there is a registered node by this name
    if ( cameraSceneNodes.find(name) != cameraSceneNodes.end() )
    {
        // return the found node
        return cameraSceneNodes[name];
    }
    // if no node found, return null
    return NULL;
}

ISceneNode* SceneManager::getMeshSceneNode(std::string name)
{
    // if there is a registered node by this name
    if ( meshSceneNodes.find(name) != meshSceneNodes.end() )
    {
        // return the found node
        return meshSceneNodes[name];
    }
    // if no node found, return null
    return NULL;
}

void SceneManager::setCurrentCamera(std::string name)
{
    // if there is a registered node by this name
    if ( cameraSceneNodes.find(name) != cameraSceneNodes.end() )
    {
        // return the found node
        currentCamera = cameraSceneNodes[name];
    }
}

CameraSceneNode* SceneManager::getCurrentCamera()
{
    return currentCamera;
}

bool SceneManager::saveScreenShot()
{
    // create a static screenshot counter - increments each time this function is called
    static int screenShotCounter = 0;
    // create a small buffer to contain the screenshot's filename
    char buffer[256];
    // render to the text buffer the proposed filename for the screenshot
    snprintf( buffer, 256, "ScreenShot%d.bmp", screenShotCounter );
    // create a string the contents of the text buffer
    std::string filename = buffer;
    // if the SDL window has been created and the proposed filename is greater than zero characters
    if ( filename.length() > 0 )
    {
        // attempts to save a screenshot
        if ( SOIL_save_screenshot(filename.c_str(), SOIL_SAVE_TYPE_BMP, 0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)) == -1 )
        {
            // Send a message to the console
            std::cout << "Error saving screenshot" << std::endl;
            // There was an error saving the bitmap
            return false;
        }
        else
        {
            // Increase the screen shot counter by one
            screenShotCounter++;
            // screenshot saved
            return true;
        }
    }
    else
    {
        // Send a message to the console
        std::cout << "Unable to take a screen shot because there is either no application window or an invalid file name " << std::endl;
        // There was an error saving the bitmap
        return false;
    }
}

void SceneManager::update()
{
    // iterate through all the scene node maps and update everything
    for ( std::map<std::string, ISceneNode*>::iterator iter = lightSceneNodes.begin() ; iter != lightSceneNodes.end() ; ++iter )
    {
        (*iter).second->update();
    }

    for ( std::map<std::string, CameraSceneNode*>::iterator iter = cameraSceneNodes.begin() ; iter != cameraSceneNodes.end() ; ++iter )
    {
        (*iter).second->update();
    }

    for ( std::map<std::string, ISceneNode*>::iterator iter = meshSceneNodes.begin() ; iter != meshSceneNodes.end() ; ++iter )
    {
        (*iter).second->update();
    }

    skySceneNode->setPosition(currentCamera->getPosition());
}

void SceneManager::draw()
{
    if ( skySceneNode != NULL )
    {
        // draw the skydome
        glPushMatrix();
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_LIGHTING);
//            glBindTexture(GL_TEXTURE_2D,skySceneNode->getMaterial().getTexture());
            skySceneNode->draw();
            glBindTexture(GL_TEXTURE_2D,0);
            glEnable(GL_LIGHTING);
            glEnable(GL_DEPTH_TEST);
        glPopMatrix();
    }

    if ( currentCamera != NULL )
    {
        currentCamera->draw();
    }

    // iterate through all the scene node maps and update everything
    for ( std::map<std::string, ISceneNode*>::iterator iter = lightSceneNodes.begin() ; iter != lightSceneNodes.end() ; ++iter )
    {
        (*iter).second->draw();
    }

    for ( std::map<std::string, ISceneNode*>::iterator iter = meshSceneNodes.begin() ; iter != meshSceneNodes.end() ; ++iter )
    {
        (*iter).second->draw();
    }
}

void SceneManager::freeResources()
{
    // iterate through all the scene node maps and delete everything
    for ( std::map<std::string, ISceneNode*>::iterator iter = lightSceneNodes.begin() ; iter != lightSceneNodes.end() ; ++iter )
    {
        delete (*iter).second;
        (*iter).second = NULL;
    }
    lightSceneNodes.clear();

    for ( std::map<std::string, CameraSceneNode*>::iterator iter = cameraSceneNodes.begin() ; iter != cameraSceneNodes.end() ; ++iter )
    {
        delete (*iter).second;
        (*iter).second = NULL;
    }
    cameraSceneNodes.clear();

    for ( std::map<std::string, ISceneNode*>::iterator iter = meshSceneNodes.begin() ; iter != meshSceneNodes.end() ; ++iter )
    {
        delete (*iter).second;
        (*iter).second = NULL;
    }
    meshSceneNodes.clear();
}
