#include "CameraSceneNode.h"


CameraSceneNode::~CameraSceneNode()
{
    //dtor
}

void CameraSceneNode::update()
{
    position.x = position.x + cos(rotation.y+90.0f*M_PI/180.0f) * strafe + cos(rotation.y)*stride;
    position.y = position.y + sin(rotation.x)*stride;
    position.z = position.z + sin(rotation.y+90.0f*M_PI/180.0f) * strafe + sin(rotation.y)*stride;

    strafe = strafe - strafe/20.0f;
    stride = stride - stride/20.0f;

    rotation = rotation + omega;
    omega = omega  - omega* (0.2f);
}

void CameraSceneNode::draw()
{
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    Vector3d lookAt(0.0f, 0.0f, 0.0f);
    lookAt.x = position.x + cos(rotation.y);
    lookAt.y = position.y + sin(rotation.x);
    lookAt.z = position.z + sin(rotation.y);

    // setup camera
    gluLookAt(position.x, position.y, position.z,
              lookAt.x, lookAt.y, lookAt.z,
              0.0f,1.0f,0.0f);
}

