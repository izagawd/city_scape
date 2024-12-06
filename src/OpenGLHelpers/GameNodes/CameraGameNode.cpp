//
// Created by theiz on 10/4/2024.
//

#include "CameraGameNode.h"

#include "../../MyWorld.h"
bool isPointInsideCube(glm::vec3 point,
                       float min_x, float min_y, float min_z,
                       float max_x, float max_y, float max_z) {
    return (point.x >= min_x && point.x <= max_x) &&
           (point.y >= min_y && point.y <= max_y) &&
           (point.z >= min_z && point.z <= max_z);
}


bool isPointInsideBuilding(glm::vec3 point, MeshGameNode* building) {
   return  isPointInsideCube(point,
            building->localTransform.translation.x - building->localTransform.scale.x,
            building->localTransform.translation.y,
            building->localTransform.translation.z - building->localTransform.scale.z,
            building->localTransform.translation.x + building->localTransform.scale.x,
            building->localTransform.translation.y + (building->localTransform.scale.y * 2),
            building->localTransform.translation.z + building->localTransform.scale.z  );
}
void CameraGameNode::update(float dt) {
    SceneGameNode::update(dt);


    //logic for camera movement
    auto mouseMovement = getWorld()->getMousePos() - lastMousePos;
    lastMousePos = getWorld()->getMousePos();


    auto previous_translation = this->localTransform.translation;
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

    auto buildings = dynamic_cast<MyWorld*>(getWorld())->buildings;
    for(auto i : buildings) {
        if(isPointInsideBuilding(localTransform.translation,i)) {
            this->localTransform.translation = previous_translation;
        }
    }
}

CameraGameNode::CameraGameNode() {
    localTransform.translation.z = -6.0f;
}

void CameraGameNode::init() {
    SceneGameNode::init();
    lastMousePos = getWorld()->getMousePos();
}
