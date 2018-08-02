#ifndef MESHFACTORY_H
#define MESHFACTORY_H

// include the input output stream
#include <iostream>
// include the utility class
#include "Utils.h"
// include the vector 2d class
#include "Vector2d.h"
// include the vector 3d class
#include "Vector3d.h"
// include the matrix4 class
#include "Matrix4.h"
// include the ply header
#include "Ply.h"
// include smesh.h
#include "SMesh.h"

class MeshFactory
{
    public:
        //! Default Constructor
        MeshFactory() {}
        //! Destructor
        virtual ~MeshFactory() {}
        //! Create null
        SMesh createNull();
        //! Create sphere
        SMesh createSphere(Vector3d position, Vector3d rotation, Vector3d size);
        //! Create cube
        SMesh createCube(Vector3d position, Vector3d rotation, Vector3d size);
        //! Create pyramid
        SMesh createSquareBasedPyramid(Vector3d position, Vector3d rotation, Vector3d size, float baseLength = 1.0f, float baseHeight = 1.0f);
        //! Create torus
        SMesh createTorus(Vector3d position, Vector3d rotation, Vector3d size, float centreOffset = 5.0f, Vector2d radius = Vector2d(1.0f, 1.0f) );
        //! Create cylinder
        SMesh createCylinder(Vector3d position, Vector3d rotation, Vector3d size, float height = 2.0f, Vector2d radius = Vector2d(1.0f, 1.0f));
        //! Create Hollow cylinder
        SMesh createHollowCylinder(Vector3d position, Vector3d rotation, Vector3d size, float height = 2.0f, Vector2d outerRadius = Vector2d(1.0f, 1.0f), Vector2d innerRadius = Vector2d(0.5f, 0.5f));
        //! Load model
        SMesh loadModel(const char* filename, Vector3d position, Vector3d rotation, Vector3d size);

    protected:
        //! Find the normal of a surface
        Vector3d findNormal(Vector3d vector1, Vector3d vector2, Vector3d vector3);

};

#endif // MESHFACTORY_H
