//
// Created by theiz on 10/4/2024.
//

#include "World.h"

#include "../GameNodes/CameraGameNode.h"
void World::destroy(GameNode *gameNode) {
    gameNodes.erase(gameNode);
}

CameraGameNode* World::getCamera() const {
    return camera;
}



void World::init() {

    glEnable(GL_DEPTH_TEST);
    _setMouseScroll(glm::vec2(0, 0));

    // spawns the camera for the world
    camera = spawnGameNode<CameraGameNode>();
}


void World::render() {
    render(m_width, m_height);
}

void World::render(int width, int height) {

    glClearColor(0.3f, 0.3f, 0.3f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 mProj = glm::perspective(glm::radians(camera->fieldOfView), (float)width / (float)height,
    camera->nearPlane, camera->farPlane);
        auto& camWorldTrans = camera->transform.translation;
        auto& camWorldRot = camera->transform.rotation;
        auto camWorldForward = camWorldRot.getForward();
        glm::mat4 mView = glm::lookAt(camWorldTrans,
                camWorldForward + camWorldTrans, camWorldRot.getUp() );
        for (auto& gameNode : gameNodes) {
            gameNode->render(width, height,mView,mProj);
            ;        }

}

void World::update(float dt) {
    if(!hasInit) {
        hasInit = true;
        init();
    }
    for (auto gameNode : gameNodes) {
        gameNode->update(dt);
    }
}

World::World( const std::string& name): App(name) {

}

