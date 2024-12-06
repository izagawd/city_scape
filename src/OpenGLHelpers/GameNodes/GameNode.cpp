//
// Created by theiz on 10/4/2024.
//

#include "GameNode.h"

#include "CameraGameNode.h"
#include "CameraGameNode.h"
#include "CameraGameNode.h"
#include "CameraGameNode.h"
#include "SceneGameNode.h"
#include "../Worlds/World.h"



GameNode::~GameNode() {
}

void GameNode::init() {
}


World* GameNode::getWorld() const {
    return world;
}

void GameNode::render(int width, int height, const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix) {

}

void GameNode::update(float dt) {

}

void GameNode::destroy() {
    getWorld()->destroy(this);
}
