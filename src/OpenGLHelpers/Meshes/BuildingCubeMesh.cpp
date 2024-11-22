//
// Created by theiz on 11/6/2024.
//

#include "BuildingCubeMesh.h"


void BuildingCubeMesh::setMeshData(std::array<unsigned char, 36> &indices, std::array<Vertex3D, 24> &triangleVertices,
    std::array<TextCoord, 24> &textCoords) {
        // Define the 24 unique vertices
    // Front face (Vertices 0-3)
    triangleVertices[0] = Vertex3D(-1, 0, 1);  // Bottom-left
    triangleVertices[1] = Vertex3D(1, 0, 1);   // Bottom-right
    triangleVertices[2] = Vertex3D(1, 2, 1);   // Top-right
    triangleVertices[3] = Vertex3D(-1, 2, 1);  // Top-left

    textCoords[0] = {0.0f, 0.0f}; // Bottom-left
    textCoords[1] = {1.0f, 0.0f}; // Bottom-right
    textCoords[2] = {1.0f, 1.0f}; // Top-right
    textCoords[3] = {0.0f, 1.0f}; // Top-left

    // Back face (Vertices 4-7)
    triangleVertices[4] = Vertex3D(1, 0, -1);   // Bottom-left
    triangleVertices[5] = Vertex3D(-1, 0, -1);  // Bottom-right
    triangleVertices[6] = Vertex3D(-1, 2, -1);  // Top-right
    triangleVertices[7] = Vertex3D(1, 2, -1);   // Top-left

    textCoords[4] = {0.0f, 0.0f}; // Bottom-left
    textCoords[5] = {1.0f, 0.0f}; // Bottom-right
    textCoords[6] = {1.0f, 1.0f}; // Top-right
    textCoords[7] = {0.0f, 1.0f}; // Top-left

    // Left face (Vertices 8-11)
    triangleVertices[8]  = Vertex3D(-1, 0, -1); // Bottom-left
    triangleVertices[9]  = Vertex3D(-1, 0, 1);  // Bottom-right
    triangleVertices[10] = Vertex3D(-1, 2, 1);  // Top-right
    triangleVertices[11] = Vertex3D(-1, 2, -1); // Top-left

    textCoords[8]  = {0.0f, 0.0f}; // Bottom-left
    textCoords[9]  = {1.0f, 0.0f}; // Bottom-right
    textCoords[10] = {1.0f, 1.0f}; // Top-right
    textCoords[11] = {0.0f, 1.0f}; // Top-left

    // Right face (Vertices 12-15)
    triangleVertices[12] = Vertex3D(1, 0, 1);   // Bottom-left
    triangleVertices[13] = Vertex3D(1, 0, -1);  // Bottom-right
    triangleVertices[14] = Vertex3D(1, 2, -1);  // Top-right
    triangleVertices[15] = Vertex3D(1, 2, 1);   // Top-left

    textCoords[12] = {0.0f, 0.0f}; // Bottom-left
    textCoords[13] = {1.0f, 0.0f}; // Bottom-right
    textCoords[14] = {1.0f, 1.0f}; // Top-right
    textCoords[15] = {0.0f, 1.0f}; // Top-left

    // Top face (Vertices 16-19)
    triangleVertices[16] = Vertex3D(-1, 2, 1);  // Bottom-left
    triangleVertices[17] = Vertex3D(1, 2, 1);   // Bottom-right
    triangleVertices[18] = Vertex3D(1, 2, -1);  // Top-right
    triangleVertices[19] = Vertex3D(-1, 2, -1); // Top-left

    textCoords[16] = {0.0f, 0.0f}; // Bottom-left
    textCoords[17] = {1.0f, 0.0f}; // Bottom-right
    textCoords[18] = {1.0f, 1.0f}; // Top-right
    textCoords[19] = {0.0f, 1.0f}; // Top-left

    // Bottom face (Vertices 20-23)
    triangleVertices[20] = Vertex3D(-1, 0, -1); // Bottom-left
    triangleVertices[21] = Vertex3D(1, 0, -1);  // Bottom-right
    triangleVertices[22] = Vertex3D(1, 0, 1);   // Top-right
    triangleVertices[23] = Vertex3D(-1, 0, 1);  // Top-left

    textCoords[20] = {0.0f, 0.0f}; // Bottom-left
    textCoords[21] = {1.0f, 0.0f}; // Bottom-right
    textCoords[22] = {1.0f, 1.0f}; // Top-right
    textCoords[23] = {0.0f, 1.0f}; // Top-left

    // Define the indices for each face (36 indices total)
    // Front face
    indices[0] = 0; indices[1] = 1; indices[2] = 2;
    indices[3] = 2; indices[4] = 3; indices[5] = 0;

    // Back face
    indices[6] = 4; indices[7] = 5; indices[8] = 6;
    indices[9] = 6; indices[10] = 7; indices[11] = 4;

    // Left face
    indices[12] = 8; indices[13] = 9; indices[14] =10;
    indices[15] =10; indices[16] =11; indices[17] = 8;

    // Right face
    indices[18] =12; indices[19] =13; indices[20] =14;
    indices[21] =14; indices[22] =15; indices[23] =12;

    // Top face
    indices[24] =16; indices[25] =17; indices[26] =18;
    indices[27] =18; indices[28] =19; indices[29] =16;

    // Bottom face
    indices[30] =20; indices[31] =21; indices[32] =22;
    indices[33] =22; indices[34] =23; indices[35] =20;
}
