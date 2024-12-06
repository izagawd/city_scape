//
// Created by theiz on 10/9/2024.
//

#include "SceneGameNode.h"





glm::mat4 SceneGameNode::getMatrix() const {
    const auto& localTranslation = transform.translation;
    const auto& localRotation = transform.rotation;
    const auto& localScale = transform.scale;
    glm::mat4 posMat = glm::translate(glm::mat4(1.0f), glm::vec3(localTranslation.x, localTranslation.y, localTranslation.z));



    glm::mat4 rotationMat = localRotation.getRotationMatrix();
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(localScale.x, localScale.y, localScale.z));

    return posMat * rotationMat * scaleMat;
}
