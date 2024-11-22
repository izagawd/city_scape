//
// Created by theiz on 10/4/2024.
//

#include "CameraGameNode.h"

void CameraGameNode::update(float dt) {
    SceneGameNode::update(dt);


    auto mouseMovement = getWorld()->getMousePos() - lastMousePos;
    lastMousePos = getWorld()->getMousePos();


    if(getWorld()->isMMBDown()) {
        this->localTransform.rotation.y += mouseMovement.x * mouseSensitivity * dt;
        this->localTransform.rotation.x -= mouseMovement.y * mouseSensitivity * dt;
    }

    if (getWorld()->isKeyDown('w')) {
        this->localTransform.translation +=
            this->localTransform.rotation.getForward() * cameraSpeed * dt;
    }
    if (getWorld()->isKeyDown('s')) {
        this->localTransform.translation -=
            this->localTransform.rotation.getForward() * cameraSpeed * dt;
    }
    if (getWorld()->isKeyDown('a')) {
        this->localTransform.translation +=
            this->localTransform.rotation.getRight() * cameraSpeed * dt;
    }
    if (getWorld()->isKeyDown('d')) {
        this->localTransform.translation -=
            this->localTransform.rotation.getRight() * cameraSpeed * dt;
    }
    // Up/Down movement
    if (getWorld()->isKeyDown(' ')) {
        this->localTransform.translation.y += cameraSpeed * dt;
    }
    if (getWorld()->isKeyDown('c')) {
        this->localTransform.translation.y -= cameraSpeed * dt;
    }
}

CameraGameNode::CameraGameNode() {
    localTransform.translation.z = -6.0f;
}

void CameraGameNode::init() {
    SceneGameNode::init();
    lastMousePos = getWorld()->getMousePos();
}
