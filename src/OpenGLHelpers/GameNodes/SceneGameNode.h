#pragma once



#include "GameNode.h"

/**
* A game node that has transform
 */
class SceneGameNode : public GameNode {

public:

    Rotation getWorldRotation() const;

    glm::vec3 getWorldTranslation() const;

    Transform localTransform = Transform();
    glm::vec3 getWorldScale() const;

    glm::mat4 getWorldMatrix() const;
};