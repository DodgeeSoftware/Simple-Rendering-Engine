#ifndef VERTEX_H
#define VERTEX_H

// include the vector 2d class
#include "Vector2d.h"
// include the vector 3d class
#include "Vector3d.h"
// include the colour structure
#include "SColour.h"

class Vertex
{
    public:
        //! Default constructor
        Vertex() {}
        //! Overloaded constructor
        Vertex(Vector3d position, Vector3d normal, Vector2d textureCoordinate)
        {
            this->position = position;
            this->normal = normal;
            this->textureCoordinate = textureCoordinate;
            SColour colour;
            colour.red = 1.0f;
            colour.green = 1.0f;
            colour.blue = 1.0f;
            colour.alpha = 0.0f;
            this->colour = colour;
        }
        //! Overloaded constructor
        Vertex(Vector3d position, Vector3d normal, Vector2d textureCoordinate, SColour colour)
        {
            this->position = position;
            this->normal = normal;
            this->textureCoordinate = textureCoordinate;
            this->colour = colour;
        }
        //! Destructor
        virtual ~Vertex() {}

        Vector3d position;
        Vector3d normal;
        Vector2d textureCoordinate;
        SColour colour;
};

#endif // VERTEX_H
