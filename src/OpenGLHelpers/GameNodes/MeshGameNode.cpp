//
// Created by theiz on 10/9/2024.
//

#include "MeshGameNode.h"

#include "CameraGameNode.h"
#include "CameraGameNode.h"
#include "CameraGameNode.h"
#include "CameraGameNode.h"
#include "../GameMaterial.h"
#include "../Meshes/PlaneMesh.h"

MeshGameNode::~MeshGameNode() {
    if(vertexArrayId != 0) {
        glDeleteVertexArrays(1, &vertexArrayId);
    }
}

void MeshGameNode::render(int width, int height, const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix) {

    auto theMesh = getMesh();
    if(theMesh != nullptr) {
        auto mat = theMesh->getMaterial();
        if(mat != nullptr) {
            GLuint programId = mat->getProgramId();

            mat->bind();
            glBindVertexArray(getVertexArrayID());
            glUniformMatrix4fv(glGetUniformLocation(programId,"world"), 1, GL_FALSE, glm::value_ptr(getMatrix()));
            glUniformMatrix4fv(glGetUniformLocation(programId,"view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
            glUniformMatrix4fv(glGetUniformLocation(programId,"projection"), 1, GL_FALSE,
                glm::value_ptr(projectionMatrix));



            glUniform2fv(glGetUniformLocation(programId,"texture_multiplier"),1,glm::value_ptr(
            mat->getTextureMultiplier()
                         ));
            theMesh->draw();
        }



    }

}



MeshGameNode::MeshGameNode() {
}

MeshBase * MeshGameNode::getMesh() const {
    return mesh;
}

void MeshGameNode::setMesh(MeshBase *mesh) {
    if(this->mesh == mesh) return;
    this->mesh = mesh;
    loadMesh();
}

GLuint MeshGameNode::getVertexArrayID() {
    if(vertexArrayId == 0) {
        glGenVertexArrays(1,&vertexArrayId);
    }
    return vertexArrayId;
}

void MeshGameNode::loadMesh() {
    auto locMesh = getMesh();
    if(locMesh != nullptr) {
        glBindVertexArray(getVertexArrayID());
        locMesh->bindAndSetAttribute();
    }
}
