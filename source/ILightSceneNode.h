#ifndef ILIGHTSCENENODE_H
#define ILIGHTSCENENODE_H

#include <ISceneNode.h>


class ILightSceneNode : public ISceneNode
{
    public:
        ILightSceneNode(SceneManager* pSceneManager) : ISceneNode(pSceneManager) {};
        virtual ~ILightSceneNode();
    protected:
    private:
};

#endif // ILIGHTSCENENODE_H
