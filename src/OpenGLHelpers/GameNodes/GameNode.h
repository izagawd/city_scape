#pragma once
#include <memory>
#include <set>
#include <stdexcept>

#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtx/transform.hpp>



#include "../Meshes/Mesh.h"
#include "../Worlds/World.h"

#include "GL/glew.h"


class World;
#include "../Rotation.h"
struct Transform {
public:
    Rotation rotation;
    glm::vec3 translation ;
    glm::vec3 scale;
    Transform() : rotation(), translation(), scale(1.0f,1.0f,1.0f) {}
};

/**
 * A game node that has no transform
 */
class GameNode {




    friend class World;
    World* world;
    public:
protected:
    virtual void init();
    virtual void render(int width, int height, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

    virtual void update(float dt);
public:
    virtual ~GameNode();
    void destroy();


    World* getWorld() const;

};


