//
// Created by theiz on 10/4/2024.
//

#include "World.h"

#include "../GameNodes/CameraGameNode.h"
#include "../GameNodes/MeshGameNode.h"
#include "../GameMaterial.h"

#include "../GameNodes/SceneGameNode.h"
#include "../Meshes/BuildingCubeMesh.h"
#include "../Meshes/PlaneMesh.h"

void World::destroy(GameNode *gameNode) {
    gameNodes.erase(gameNode);
}

CameraGameNode* World::getCamera() const {
    return camera;
}

wolf::Texture* World::buildingOne   = nullptr;
wolf::Texture* World::buildingTwo   = nullptr;
void World::init() {

    glEnable(GL_DEPTH_TEST);
    _setMouseScroll(glm::vec2(0, 0));

    // spawns the camera for the world
    camera = spawnGameNode<CameraGameNode>();
    buildingOne   = wolf::TextureManager::CreateTexture("data/building_one.png");
    buildingTwo   = wolf::TextureManager::CreateTexture("data/building_two.png");

    // creating the textures and mesh
    auto generalShader = new Shader("data/normal_texture_vertex_shader.vsh",
                              "data/normal_texture_pixel_shader.fsh");
    groundMaterial =    new GameMaterial(wolf::TextureManager::CreateTexture("data/ground_texture.png"),
                                         generalShader);
    groundMaterial->setTextureMultiplier(glm::vec2(100,100));



    planeMesh = new PlaneMesh();
    planeMesh->setMaterial(groundMaterial);

    auto buildingCubeMaterialOne =
        new GameMaterial(buildingOne,
                                 generalShader);
    buildingCubeMaterialOne->setTextureMultiplier(glm::vec2(1,3));

    auto buildingCubeMeshOne = new BuildingCubeMesh();

    buildingCubeMeshOne->setMaterial(buildingCubeMaterialOne);
    possibleBuildingMeshes.push_back(buildingCubeMeshOne);

    auto buildingCubeMaterialTwo =
        new GameMaterial(buildingTwo,
                                 generalShader);
    auto buildingCubeMeshTwo = new BuildingCubeMesh();
    buildingCubeMeshTwo->setMaterial(buildingCubeMaterialTwo);
    buildingCubeMaterialTwo->setTextureMultiplier(glm::vec2(1,3));
    possibleBuildingMeshes.push_back(buildingCubeMeshTwo);
    regenerateWorld();
    getCamera()->transform.translation.z -= 10;
}


void World::render() {
    const auto width = m_width;
    const auto height = m_height;
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
        gameNode->render(width,height,mView,mProj);
    }

}


void World::regenerateWorld() {
    const int building_square_length  = 10;
    const int groundOffset = -30;

    // removing previous buildings
    for(auto i : buildings) {
        i->destroy();
        delete i;
    }

    buildings.clear();



    const auto building_square_gap = -325;

    // generating new buildingsz
    for(auto locationOffset : {glm::vec3(0,0,0),
        glm::vec3(building_square_gap,0,0),
    glm::vec3(0,0,building_square_gap),
    glm::vec3(building_square_gap,0,building_square_gap),}) {
        for(int i = 0; i < building_square_length; i++) {
            for( int j = 0; j < building_square_length; j++) {
                auto building = spawnGameNode<MeshGameNode>();
                auto randomIndex = rand() % possibleBuildingMeshes.size();
                building->setMesh(possibleBuildingMeshes[randomIndex]);
                const auto building_gap = 30;
                building->transform.translation = glm::vec3(i * building_gap,groundOffset,

                j * building_gap) + locationOffset;
                building->transform.scale = glm::vec3(6 + (rand() % 6),15 + (rand() % 15), 6 + (rand() % 6));
                buildings.push_back(building);
            }
        }
    }
    ground = spawnGameNode<MeshGameNode>();
    ground->setMesh(planeMesh);
    ground->transform.scale = glm::vec3(350,1,350);
    ground->transform.translation.y = groundOffset;
}

void World::update(float dt) {
    if(!hasInit) {
        hasInit = true;
        init();
    }
    for (auto gameNode : gameNodes) {
        gameNode->update(dt);
    }
    if(this->isKeyJustDown('r')) {
        regenerateWorld();
    }

}

World::World( ): App("My World") {

}

