
#pragma once
#include "VertexHelpers.h"


/**
 * used to represent the three vertices required to make a triangle
 */
struct TriangleVertices{

    Vertex3D vertices[3];
    TriangleVertices(Vertex3D v1, Vertex3D v2, Vertex3D v3) {
        vertices[0] = v1;
        vertices[1] = v2;
        vertices[2] = v3;
    }
    TriangleVertices() {}
};
