#pragma once



#include "GameNode.h"

/**
* A game node that has transform
 */
class SceneGameNode : public GameNode {

public:

    Rotation getWorldRotation() const {
        glm::mat4 modelMatrix = getWorldMatrix(); // Your 4x4 transformation matrix

        // Extract the rotation matrix (3x3 upper-left part)
        glm::mat3 rotationMatrix = glm::mat3(modelMatrix);

        // Convert rotation matrix to quaternion
        glm::quat rotationQuat = glm::quat_cast(rotationMatrix);

        // Convert quaternion to Euler angles (in radians)
        glm::vec3 eulerAngles = glm::eulerAngles(rotationQuat);

        return Rotation(degrees(eulerAngles));

    }
    glm::vec3 getWorldTranslation() const {
        return getWorldMatrix()[3];
    }
    Transform localTransform = Transform();
    glm::vec3 getWorldScale() const {
        // Extract the world matrix
        glm::mat4 modelMatrix = getWorldMatrix();


        glm::vec3 scaleX = glm::vec3(modelMatrix[0]); // X basis vector
        glm::vec3 scaleY = glm::vec3(modelMatrix[1]); // Y basis vector
        glm::vec3 scaleZ = glm::vec3(modelMatrix[2]); // Z basis vector

        float scaleXLength = glm::length(scaleX);
        float scaleYLength = glm::length(scaleY);
        float scaleZLength = glm::length(scaleZ);

        return glm::vec3(scaleXLength, scaleYLength, scaleZLength);
    }
    glm::mat4 getWorldMatrix() const;
};