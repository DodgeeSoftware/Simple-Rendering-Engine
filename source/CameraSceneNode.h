#ifndef CAMERASCENENODE_H
#define CAMERASCENENODE_H

// include the openGL header
#include <gl/gl.h>
// include the opengl extension header
#include <gl/glext.h>
// include the openGL Utility header
#include <gl/glu.h>
// include the utility class
#include "Utils.h"
// include the vector 2d class
#include "Vector2d.h"
// include the vector 3d class
#include "Vector3d.h"
// include the scenenode
#include "ISceneNode.h"


class CameraSceneNode : public ISceneNode
{
    public:
        //! Default constructor
        CameraSceneNode(SceneManager* pSceneManager) : ISceneNode(pSceneManager) {strafe = 0.0f; stride = 0.0f; }
        //! Destructor
        virtual ~CameraSceneNode();
        //! Render the scene node
        virtual void update();
        //! Render the scene node
        virtual void draw();
        //! Get Stride
        float getStride() { return this->stride; }
        //! Set Stride
        void setStride(float stride) { this->stride = stride; }
        //! Get Strafe
        float getStrafe() { return this->strafe; }
        //! Set Stride
        void setStrafe(float strafe) { this->strafe = strafe; }

    protected:
        //! forward movement
        float stride;
        //! left and right movement
        float strafe;

};

#endif // CAMERASCENENODE_H
