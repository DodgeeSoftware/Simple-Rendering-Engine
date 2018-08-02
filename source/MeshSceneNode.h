#ifndef MESHSCENENODE_H
#define MESHSCENENODE_H

// include the openGL header
#include <gl/gl.h>
// include the opengl extension header
#include <gl/glext.h>
// include the openGL Utility header
#include <gl/glu.h>
// include the ISceneNode class
#include <ISceneNode.h>
// inlclude the smesh.h class
#include "SMesh.h"

/** **/
class MeshSceneNode : public ISceneNode
{
    public:
        //! Default constructor
        MeshSceneNode(SceneManager* pSceneManager) : ISceneNode(pSceneManager) {}
        //! Destructor
        virtual ~MeshSceneNode() {}
        //! Get the mesh
        virtual SMesh getMesh() { return mesh; }
        //! Set the mesh
        virtual void setMesh(SMesh mesh) { this->mesh = mesh; }
        //! update
        virtual void update();
        //! draw
        virtual void draw();

    protected:
        //! local mesh
        SMesh mesh;
};

#endif // MESHSCENENODE_H
