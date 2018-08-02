#ifndef BILLBOARDSCENENODE_H
#define BILLBOARDSCENENODE_H

#include <ISceneNode.h>


class BillboardSceneNode : public ISceneNode
{
    public:
        BillboardSceneNode(SceneManager* pSceneManager) : ISceneNode(pSceneManager) {};
        virtual ~BillboardSceneNode();
    protected:
    private:
};

#endif // BILLBOARDSCENENODE_H
