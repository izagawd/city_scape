//
// Created by theiz on 11/6/2024.
//

#ifndef MYWORLD_H
#define MYWORLD_H
#include "OpenGLHelpers/GameMaterial.h"

#include "OpenGLHelpers/GameNodes/CameraGameNode.h"
#include "OpenGLHelpers/GameNodes/MeshGameNode.h"
#include "OpenGLHelpers/GameNodes/SceneGameNode.h"
#include "OpenGLHelpers/Meshes/BuildingCubeMesh.h"
#include "OpenGLHelpers/Meshes/PlaneMesh.h"
#include "OpenGLHelpers/Worlds/World.h"


class MyWorld : public World {
public:
    MyWorld() : World("My World"){}

    std::vector<BuildingCubeMesh*> possibleBuildingMeshes;
    MeshGameNode* ground;
    void regenerateWorld();
    void update(float deltaTime) override;



    // mmaterial for the ground used
    GameMaterial* groundMaterial;
    // mesh for the ground used
    PlaneMesh* planeMesh;
    std::vector<MeshGameNode*> buildings;
    void init() override;
};



#endif //MYWORLD_H
