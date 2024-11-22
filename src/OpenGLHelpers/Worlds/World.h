#pragma once
#include <set>

#include "GL/glew.h"

class CameraGameNode;
class Game;
class GameNode;
#include "../../wolf/wolf.h"

class World : public wolf::App {

    bool hasInit = false;
    /**
     * All game nodes that are in the game
     */
    std::set<GameNode*> gameNodes;
    /**
     * Current camera being used
     */
    CameraGameNode* camera = nullptr;
protected:

    void render() override;
    virtual void render(int width, int height);

    virtual void init();
    virtual void update(float dt);


public:

    World(const std::string& name );

    void destroy(GameNode* gameNode);

    /**
     *
     * @return Current camera that is being used
     */
    CameraGameNode* getCamera() const;



    GLuint getProgramId();


    /**
     *
     * @return all the game nodes that are in this world
     */
    const std::set<GameNode*>& getGameNodes() const {
        return gameNodes;
    }

    /**
     *
     * @tparam TGameNode The type of the game node you want to spawn
     * @return the game node that was spawned
     */
    template<class TGameNode>
    TGameNode* spawnGameNode();
private:
    void addGameNodeAndItsChildren(GameNode* gameNode);
};

template<class TGameNode>
TGameNode* World::spawnGameNode() {
    static_assert(std::is_base_of<GameNode, TGameNode>::value || std::is_same<GameNode, TGameNode>::value,
        "template must be of type game node or subclass of it");
    auto gameNode = new TGameNode();
    addGameNodeAndItsChildren(gameNode);
    gameNode->init();
    return gameNode;

};

