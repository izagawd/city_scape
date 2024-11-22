#pragma once
#include "CameraGameNode.h"
#include "CameraGameNode.h"
#include "CameraGameNode.h"
#include "CameraGameNode.h"
#include "SceneGameNode.h"

class GameMaterial;
/**
 * Game node that can be rendered into triangles using a mesh. A material is required for rendering
 */
class MeshGameNode : public SceneGameNode {
    /**
     * The mesh to use
     */
    MeshBase* mesh  = nullptr;

    GLuint vertexArrayId = 0;

public:


    virtual ~MeshGameNode() {
        if(vertexArrayId != 0) {
            glDeleteVertexArrays(1, &vertexArrayId);
        }
    }
    void render(int width, int height, const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix) override;



    MeshGameNode();

    /**
     *
     * @return the mesh used to render this mesh game node
     */
    MeshBase* getMesh() const;

    /**
     *
     * @param mesh new mesh used to render this mesh game node
     */
    void setMesh(MeshBase *mesh);

    virtual GLuint getVertexArrayID() {
        if(vertexArrayId == 0) {
            glGenVertexArrays(1,&vertexArrayId);
        }
        return vertexArrayId;
    }

    /**
     * Helps connecting attributes to vertex array
     */
    virtual void loadMesh();
};
