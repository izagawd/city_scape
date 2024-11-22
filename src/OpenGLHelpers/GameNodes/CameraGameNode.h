
#pragma once
#include "GameNode.h"
#include "SceneGameNode.h"

/**
 * Game node that is the camera. changing its transform means changing the cameras transform
 */
class CameraGameNode : public SceneGameNode{

public:
    void update(float dt) override;
    CameraGameNode();
    void init() override;
    glm::vec2 lastMousePos;
    float mouseSensitivity = 5;
    float cameraSpeed = 10;
    GLfloat fieldOfView = 60.0f;
    GLfloat nearPlane = 0.1f;
    GLfloat farPlane = 1000.0f;
};


