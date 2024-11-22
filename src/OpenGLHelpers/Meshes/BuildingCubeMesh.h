//
// Created by theiz on 11/6/2024.
//

#ifndef BUILDINGCUBEMESH_H
#define BUILDINGCUBEMESH_H
#include "MeshIndices.h"


/**
 * Mesh where
 */
class BuildingCubeMesh : public MeshIndices<12,24,GLubyte>{

public:

    void setMeshData(std::array<unsigned char, 36> &indices, std::array<Vertex3D, 24> &triangleVertices, std::array<TextCoord, 24> &textCoords) override;
};



#endif //BUILDINGCUBEMESH_H
