#include "ISceneNode.h"

ISceneNode::ISceneNode(SceneManager* pSceneManager)
{
    this->pSceneManager = pSceneManager;
    scale = Vector3d(1.0f, 1.0f, 1.0f);
}

ISceneNode::~ISceneNode()
{
    //dtor
}
