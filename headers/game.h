#ifndef GAME_H
#define GAME_H

#include <vector>
#include <unordered_map>
#include "component.h"
#include "entity.h"
#include "player.h"
#include "system.h" // Include System definitions

class Game
{
private:
    std::unordered_map<int, std::vector<Component *>> entityComponentMap; // Map from entity ID to components
    std::vector<System *> systems;

    Player *player;

public:
    Game()
    {
        player = CreatePlayer();
    }

    // Function to create and add entities to the ECS
    Player *CreatePlayer();
    Actor *CreateActor();
    Item *CreateItem();
    Prop *CreateProp();

    Player *GetPlayer()
    {
        return player;
    }

    void Shoot()
    {
    }

    void Update(float deltaTime);

    std::vector<std::tuple<SpriteComponent *, TransformComponent *, AnimationComponent *>> GetSpriteInfo();
};

#endif
// GAME_H