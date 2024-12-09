//
// Created by theiz on 11/6/2024.
//

#include "MyWorld.h"

void MyWorld::regenerateWorld() {
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


void MyWorld::update(float deltaTime) {
    World::update(deltaTime);
    if(this->isKeyJustDown('r')) {
        regenerateWorld();
    }

    auto cam = getCamera();


}

void MyWorld::init() {
    World::init();

    // creating the textures and mesh
    auto generalShader = new Shader("data/normal_texture_vertex_shader.vsh",
                              "data/normal_texture_pixel_shader.fsh");
    groundMaterial =    new GameMaterial(wolf::TextureManager::CreateTexture("data/ground_texture.png"),
                                         generalShader);
    groundMaterial->setTextureMultiplier(glm::vec2(100,100));



    planeMesh = new PlaneMesh();
    planeMesh->setMaterial(groundMaterial);

    auto buildingCubeMaterialOne =
        new GameMaterial(wolf::TextureManager::CreateTexture("data/building_one.png"),
                                 generalShader);
    buildingCubeMaterialOne->setTextureMultiplier(glm::vec2(1,3));

    auto buildingCubeMeshOne = new BuildingCubeMesh();

    buildingCubeMeshOne->setMaterial(buildingCubeMaterialOne);
    possibleBuildingMeshes.push_back(buildingCubeMeshOne);

    auto buildingCubeMaterialTwo =
        new GameMaterial(wolf::TextureManager::CreateTexture("data/building_two.png"),
                                 generalShader);
    auto buildingCubeMeshTwo = new BuildingCubeMesh();
    buildingCubeMeshTwo->setMaterial(buildingCubeMaterialTwo);
    buildingCubeMaterialTwo->setTextureMultiplier(glm::vec2(1,3));
    possibleBuildingMeshes.push_back(buildingCubeMeshTwo);
    regenerateWorld();
    getCamera()->transform.translation.z -= 10;
}
