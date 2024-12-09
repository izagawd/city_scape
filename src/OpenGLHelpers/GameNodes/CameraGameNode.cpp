//
// Created by theiz on 10/4/2024.
//

#include "CameraGameNode.h"

#include "MeshGameNode.h"
#include "../Worlds/World.h"
bool isPointInsideCube(glm::vec3 point,
                       float min_x, float min_y, float min_z,
                       float max_x, float max_y, float max_z) {


    // sometimes camera can still see building, so this offset makes the cube collider a lil bigger to
    // prevent that from happening
    const auto collisionOffset = 1;
    return (point.x + collisionOffset >= min_x && point.x  - collisionOffset<= max_x) &&
           (point.y + collisionOffset>= min_y && point.y - collisionOffset <= max_y) &&
           (point.z + collisionOffset >= min_z && point.z  - collisionOffset<= max_z);
}


bool isPointInsideBuilding(glm::vec3 point, MeshGameNode* building) {
   return  isPointInsideCube(point,
            building->transform.translation.x - building->transform.scale.x,
            building->transform.translation.y,
            building->transform.translation.z - building->transform.scale.z,
            building->transform.translation.x + building->transform.scale.x,
            building->transform.translation.y + (building->transform.scale.y * 2),
            building->transform.translation.z + building->transform.scale.z  );
}
void CameraGameNode::update(float dt) {
    SceneGameNode::update(dt);

    if(this->getWorld()->isKeyJustDown('i')){
        invertY = !invertY;
    }
    if(this->getWorld()->isKeyJustDown(GLFW_KEY_UP)) {
        this->cameraSpeed += 3;
    }
    if(this->getWorld()->isKeyJustDown(GLFW_KEY_DOWN)) {
        this->cameraSpeed += -3;
        if(this->cameraSpeed <= 0) {
            this->cameraSpeed = 3;
        }
    }
    //logic for camera movement
    auto mouseMovement = getWorld()->getMousePos() - lastMousePos;
    if(invertY){
        mouseMovement.y *= -1;
    }
    mouseMovement.x *= -1;
    lastMousePos = getWorld()->getMousePos();


    auto previous_translation = this->transform.translation;
    if(getWorld()->isMMBDown()) {
        this->transform.rotation.y += mouseMovement.x * mouseSensitivity * dt;
        this->transform.rotation.x -= mouseMovement.y * mouseSensitivity * dt;
    }

    if (getWorld()->isKeyDown('w')) {
        this->transform.translation +=
            this->transform.rotation.getForward() * cameraSpeed * dt;
    }
    if (getWorld()->isKeyDown('s')) {
        this->transform.translation -=
            this->transform.rotation.getForward() * cameraSpeed * dt;
    }
    if (getWorld()->isKeyDown('a')) {
        this->transform.translation +=
            this->transform.rotation.getRight() * cameraSpeed * dt;
    }
    if (getWorld()->isKeyDown('d')) {
        this->transform.translation -=
            this->transform.rotation.getRight() * cameraSpeed * dt;
    }
    // Up/Down movement
    if (getWorld()->isKeyDown(' ')) {
        this->transform.translation.y += cameraSpeed * dt;
    }
    if (getWorld()->isKeyDown('c')) {
        this->transform.translation.y -= cameraSpeed * dt;
    }
    auto worldToWorkWith = getWorld();
    auto buildings = worldToWorkWith->buildings;
    auto& za_translation = transform.translation;
    // Handling collision with buildings
    for(auto i : buildings) {
        if(isPointInsideBuilding(transform.translation,i)) {

            // adding sliding collision...    
            if (!isPointInsideBuilding(glm::vec3(za_translation.x, previous_translation.y, za_translation.z), i)) {
                za_translation = glm::vec3(za_translation.x, previous_translation.y, za_translation.z);
            } 

            else if (!isPointInsideBuilding(glm::vec3(previous_translation.x, za_translation.y, za_translation.z), i)) {
                za_translation = glm::vec3(previous_translation.x, za_translation.y, za_translation.z);
            }
            else if (!isPointInsideBuilding(glm::vec3(za_translation.x, za_translation.y, previous_translation.z), i)) {
                za_translation = glm::vec3(za_translation.x, za_translation.y, previous_translation.z);
            }

            else {
                this->transform.translation = previous_translation;
            }
        }
    }

    const auto groundCollisionOffset = 1;
    // Handling ground collision...
    if(transform.translation.y - groundCollisionOffset < worldToWorkWith->ground->transform.translation.y) {
        transform.translation.y = worldToWorkWith->ground->transform.translation.y + groundCollisionOffset;
    }
}

CameraGameNode::CameraGameNode() {
    transform.translation.z = -6.0f;
}

void CameraGameNode::init() {
    SceneGameNode::init();
    lastMousePos = getWorld()->getMousePos();
}
