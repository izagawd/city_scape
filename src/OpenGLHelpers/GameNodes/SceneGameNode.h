#pragma once



#include "GameNode.h"

/**
* A game node that has transform
 */
class SceneGameNode : public GameNode {

public:


    Transform transform = Transform();

    glm::mat4 getMatrix() const;
};