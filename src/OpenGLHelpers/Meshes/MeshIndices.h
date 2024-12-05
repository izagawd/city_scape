#pragma once
#include "Mesh.h"


struct TextCoord {
    public:
    float u,v;
};
/**
 * Mesh class that handles the generation and rendering of triangles with the help of indices
 * @tparam TNumOfTriangles Number of triangles this mesh has
 * @tparam TNumOfVertices Number of vertices this mesh has, which will then be used by indices (for a cube ideally we will use 8)
 * @tparam TIndicesType The indices type to use for the mesh. (can only be unsigned byte, unsigned short and unsigned int. if not error will be thrown)
 */
template<int TNumOfTriangles, int TNumOfVertices, typename TIndicesType>
class MeshIndices : public MeshBase {
  protected:


    virtual void setMeshData(std::array<TIndicesType, TNumOfTriangles * 3>& indices,
        std::array<Vertex3D, TNumOfVertices>& triangleVertices, std::array<TextCoord, TNumOfVertices>& textCoords) = 0;
public:
    ~MeshIndices() override{
        if(indicesBufferId != 0) {
            glDeleteBuffers(1, &indicesBufferId);
        }
        if(trianglesVerticesBufferId != 0) {
            glDeleteBuffers(1, &trianglesVerticesBufferId);
        }
    }


    void draw() const override {
        // checks to ensure that the provided indices type is a ubyte, uint or ushort,
        // also helps to tell gl the proper type
        constexpr int count = TNumOfTriangles * 3;
        constexpr bool isUnsignedByte = std::is_same<TIndicesType, GLubyte>::value;
        constexpr bool isUnsignedInt = std::is_same<TIndicesType, GLuint>::value
        || std::is_same<TIndicesType, unsigned int>::value;
        constexpr bool isUnsignedShort = std::is_same<TIndicesType, GLushort>::value
  || std::is_same<TIndicesType, unsigned short>::value;

        if constexpr (isUnsignedByte) {
            glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_BYTE,0);
        } else if constexpr(isUnsignedInt) {
            glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT,0);
        } else if constexpr(isUnsignedShort) {
            glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT,0);
        } else {
            static_assert(isUnsignedByte || isUnsignedInt || isUnsignedShort, "Template TIndicesType should be uint, ubyte or ushort. nothing else");
        }

    }
    GLuint textCoordId = 0;
    GLuint indicesBufferId = 0;
    GLuint trianglesVerticesBufferId = 0;
protected:
    void bindAndSetAttribute(GLuint programId) override {

        if(trianglesVerticesBufferId == 0 || indicesBufferId == 0 || textCoordId == 0) {
            std::array<TIndicesType, TNumOfTriangles * 3> indices;
            std::array<Vertex3D, TNumOfVertices> triangleVertices;
            std::array<TextCoord, TNumOfVertices> textCoords;
            setMeshData(indices, triangleVertices, textCoords);
            if(trianglesVerticesBufferId == 0) {
                glGenBuffers(1, &trianglesVerticesBufferId);
                glBindBuffer(GL_ARRAY_BUFFER, trianglesVerticesBufferId);

                glBufferData(GL_ARRAY_BUFFER,sizeof(triangleVertices),&triangleVertices,GL_STATIC_DRAW);
            }
            if(indicesBufferId == 0) {
                glGenBuffers(1, &indicesBufferId);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferId);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),&indices,GL_STATIC_DRAW);
            }
            if(textCoordId == 0) {
                glGenBuffers(1, &textCoordId);
                glBindBuffer(GL_ARRAY_BUFFER, textCoordId);
                glBufferData(GL_ARRAY_BUFFER,sizeof(textCoords),&textCoords,GL_STATIC_DRAW);
            }
        }
        glBindBuffer(GL_ARRAY_BUFFER, trianglesVerticesBufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferId);
        int iPosAttr = glGetAttribLocation(programId, "a_position");
        glVertexAttribPointer(iPosAttr,         // Attribute location
                               3,                // Number of components
                               GL_FLOAT, // Type of each component
                               GL_FALSE,          // Normalize?
                               0,                // Stride
                               0);               // Offset
        glEnableVertexAttribArray(iPosAttr);
        glBindBuffer(GL_ARRAY_BUFFER, textCoordId);
        int iTexCoordAttr = glGetAttribLocation(programId, "a_tex_coord");
        glVertexAttribPointer(iTexCoordAttr,2,GL_FLOAT,GL_FALSE,0,0);
        glEnableVertexAttribArray(iTexCoordAttr);
    }
};

