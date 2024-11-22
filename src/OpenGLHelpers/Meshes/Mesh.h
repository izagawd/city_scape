#pragma once
#include <array>
#include <iostream>


#include "TriangleVertices.h"
#include "../GameMaterial.h"
#include "GL/glew.h"


class GameMaterial;
/**
 * Mesh class that handles the generation and rendering of triangles
 */
class MeshBase {


    GameMaterial* material;

    public:

    void setMaterial(GameMaterial* material) {
        this->material = material;
        if(material != nullptr) {
            bindAndSetAttribute();
        }

    }
    GameMaterial* getMaterial()  const{
        return material;
    }
    virtual ~MeshBase() {}

    GameMaterial* getMaterial() {
        return material;
    }
    virtual void draw() const = 0;

    void bindAndSetAttribute() {
        if(material != nullptr) {
            bindAndSetAttribute(material->getProgramId());
        }
    }
    protected:
    virtual void bindAndSetAttribute(GLuint programId) = 0;

};


/**
 * Mesh class that handles the generation and rendering of triangles without the use of indices
 * @tparam TNumOfTriangles Number of triangles this mesh has
 */
template<int TNumOfTriangles>
class Mesh : public MeshBase {
protected:
    virtual void setTriangleVertices(std::array<TriangleVertices,TNumOfTriangles>& trianglesVertices) = 0;
public:

     ~Mesh(){
        if(trianglesVerticesBufferId != 0) {
            glDeleteBuffers(1, &trianglesVerticesBufferId);
        }
    }
    void draw() const override {
        glDrawArrays(GL_TRIANGLES, 0, TNumOfTriangles * 3);
    }
    GLuint trianglesVerticesBufferId = 0;

    GLuint getBufferId() {
        return trianglesVerticesBufferId;
    }


    void bindAndSetAttribute(GLuint programId) override {

        if(trianglesVerticesBufferId == 0) {
            glGenBuffers(1, &trianglesVerticesBufferId);
            glBindBuffer(GL_ARRAY_BUFFER, trianglesVerticesBufferId);

            std::array<TriangleVertices,TNumOfTriangles> trianglesVertices;
            setTriangleVertices(trianglesVertices);
            glBufferData(GL_ARRAY_BUFFER,sizeof(trianglesVertices),trianglesVertices,GL_STATIC_DRAW);

        }else {
            glBindBuffer(GL_ARRAY_BUFFER, trianglesVerticesBufferId);
        }
        int iPosAttr = glGetAttribLocation(programId, "a_position");
        glVertexAttribPointer(iPosAttr,         // Attribute location
                               3,                // Number of components
                               GL_FLOAT, // Type of each component
                               GL_FALSE,          // Normalize?
                               0,                // Stride
                               0);               // Offset
        glEnableVertexAttribArray(iPosAttr);
    }


};

