//
// Created by theiz on 10/4/2024.
//

#pragma once

#include "MeshIndices.h"

/**
 * Cube mesh, to help avoid code repetition
 */
class CubeMesh : public MeshIndices<12,24,GLubyte>{


public:

 void setMeshData(std::array<unsigned char, 36> &indices, std::array<Vertex3D, 24> &triangleVertices, std::array<TextCoord, 24> &textCoords) override;
};


