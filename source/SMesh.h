#ifndef SMESH_H
#define SMESH_H

// include the stl vector class
#include <vector>
// include the SMeshBuffer class
#include "SMeshBuffer.h"

struct SMesh
{
    std::vector<SMeshBuffer> meshBuffers;
};

#endif // SMESH_H
