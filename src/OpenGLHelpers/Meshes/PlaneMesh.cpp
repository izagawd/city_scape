#include "PlaneMesh.h"

#include <glm/vec3.hpp>


void PlaneMesh::setMeshData(std::array<unsigned char, 6> &indices, std::array<Vertex3D, 4> &triangleVertices,
    std::array<TextCoord, 4> &textCoords) {
    triangleVertices[0] = Vertex3D(-1, 0, -1); // Bottom left
    triangleVertices[1] = Vertex3D(1, 0, -1);  // Bottom right
    triangleVertices[2] = Vertex3D(1,0, 1);   // Top right
    triangleVertices[3] = Vertex3D(-1, 0, 1);  // Top left
    textCoords[0] ={1,1};
    textCoords[1]={0,1};
    textCoords[2]={0,0};
    textCoords[3]={1,0};

    indices[0] = 0; indices[1] = 1; indices[2] = 2;  // First triangle
    indices[3] = 2; indices[4] = 3; indices[5] = 0;
}
