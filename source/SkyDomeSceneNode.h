#ifndef SKYDOMESCENENODE_H
#define SKYDOMESCENENODE_H

#include <ISceneNode.h>


class SkyDomeSceneNode : public ISceneNode
{
    public:
        SkyDomeSceneNode(SceneManager* pSceneManager) : ISceneNode(pSceneManager) {};
        virtual ~SkyDomeSceneNode();
    protected:
    private:
};

#endif // SKYDOMESCENENODE_H
