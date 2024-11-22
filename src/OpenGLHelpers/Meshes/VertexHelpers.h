#pragma once
#include "../../../thirdparty/glew/include/GL/glew.h"

/**
 * Used to describe a point in 3D space for a triangle vertex
 */
struct Vertex3D{

public:
    GLfloat VertexComponents[3];

    Vertex3D() : Vertex3D(0,0,0){

    }
    Vertex3D(GLfloat VertexComponent1,GLfloat VertexComponent2, GLfloat VertexComponent3){
        VertexComponents[0] = VertexComponent1;
        VertexComponents[1] = VertexComponent2;
        VertexComponents[2] = VertexComponent3;
    }
};
