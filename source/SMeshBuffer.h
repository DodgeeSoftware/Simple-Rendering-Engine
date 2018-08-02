#ifndef MESHBUFFER_H
#define MESHBUFFER_H

// include the stl vector class
#include <vector>
// include the Vertex structure
#include "Vertex.h"

struct SMeshBuffer
{
    std::vector<unsigned int> indices;
    std::vector<Vertex> vertices;
};

#endif // MESHBUFFER_H
