#ifndef ISCENENODE_H
#define ISCENENODE_H

// include the utility class
#include "Utils.h"
// include the vector 2d class
#include "Vector2d.h"
// include the vector 3d class
#include "Vector3d.h"
// include the matrix4 class
#include "Matrix4.h"
// include the material class
#include "Material.h"

// scene manager predeclaration
class SceneManager;

class ISceneNode
{
    public:
        //! Default constructor
        ISceneNode(SceneManager* pSceneManager);
        //! Destructor
        virtual ~ISceneNode();
        //! Get the position of the scene node
        virtual Vector3d getPosition() { return this->position; }
        //! Set the position of the scene node
        virtual void setPosition(Vector3d position) { this->position = position; }
        //! Get the velocity of the scene node
        virtual Vector3d getVelocity() { return this->velocity; }
        //! Set the velocity of the scene node
        virtual void setVelocity(Vector3d velocity) { this->velocity = velocity; }
        //! Get the omega of the scene node
        virtual Vector3d getOmega() { return this->omega; }
        //! Set the velocity of the scene node
        virtual void setOmega(Vector3d omega) { this->omega = omega; }
        //! Get the rotation of the scene node
        virtual Vector3d getRotationDegrees() { return this->rotation * RAD2DEG; }
        //! Set the rotation of the scene node
        virtual void setRotationDegrees(Vector3d rotation) { this->rotation = rotation * DEG2RAD; }
        //! Get the scale of the scene node
        virtual Vector3d getScale() { return this->scale; }
        //! Set the scale of the scene node
        virtual void setScale(Vector3d scale) { this->scale = scale; }
        //! Render the scene node
        virtual void update() = 0;
        //! Render the scene node
        virtual void draw() = 0;
        //! Get material
        virtual Material getMaterial() { return material; }
        //! Set material
        virtual void setMaterial(Material material) { this->material = material; }

    protected:
        //! A pointer to the scene manager
        SceneManager* pSceneManager;
        //! A vector representing the position of the scene node
        Vector3d position;
        //! A vector representing the velocity of the scene node
        Vector3d velocity;
        //! A vector representing the rotation of the scene node
        Vector3d rotation;
        //! A vector representing the omega of the scene node
        Vector3d omega;
        //! A vector representing the scale of the scene node
        Vector3d scale;
        //! A material for this scene node
        Material material;
};

#endif // ISCENENODE_H
