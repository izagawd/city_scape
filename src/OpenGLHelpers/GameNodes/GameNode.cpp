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

void GameNode::setParent(GameNode *inParent) {

    if(parent  == inParent) return;
    if(parent != nullptr) {
        parent->children.erase(this);
    }
    if(inParent != nullptr)
        inParent->children.insert(this);
    parent = inParent;

}

const std::set<GameNode *> & GameNode::getChildren() const {
    return children;
}

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


glm::mat4 SceneGameNode::getWorldMatrix() const {
    const auto& localTranslation = localTransform.translation;
    const auto& localRotation = localTransform.rotation;
    const auto& localScale = localTransform.scale;
    glm::mat4 posMat = glm::translate(glm::mat4(1.0f), glm::vec3(localTranslation.x, localTranslation.y, localTranslation.z));



    glm::mat4 rotationMat = localRotation.getRotationMatrix();
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(localScale.x, localScale.y, localScale.z));

    // code below checks the nearest parent game node with transform, and then follows that transform
    // remember: scene game nodes are the nodes with transform
    auto localMatrix = posMat * rotationMat * scaleMat;
    SceneGameNode* parentToPick = nullptr;
    GameNode* currentParent = getParent();
    while(currentParent != nullptr && parentToPick == nullptr) {
        parentToPick = dynamic_cast<SceneGameNode*>(currentParent);
        currentParent = currentParent->getParent();
    }
    if(parentToPick != nullptr){
        localMatrix = parentToPick->getWorldMatrix() * localMatrix;
    }
    return localMatrix;
}

void GameNode::destroy() {
    getWorld()->destroy(this);
}
