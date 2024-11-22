#pragma once
#include "MeshIndices.h"


class PlaneMesh : public MeshIndices<2,4,GLubyte>

{
public:
    void setMeshData(std::array<unsigned char, 6> &indices, std::array<Vertex3D, 4> &triangleVertices, std::array<TextCoord, 4> &textCoords) override;

};
