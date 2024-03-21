#ifndef GAME_H
#define GAME_H

#include <vector>
#include <unordered_map>
#include "component.h"
#include "entity.h"
#include "system.h" // Include System definitions

class Game
{
private:
    std::unordered_map<int, std::vector<Component *>> entityComponentMap; // Map from entity ID to components
    std::vector<System *> systems;

public:
    Game()
    {
    }

    // Function to create and add entities to the ECS
    Actor *CreateActor();

    Item *CreateItem();

    Prop *CreateProp();

    void Shoot()
    {
    }

    void Update(float deltaTime);
};

#endif
// GAME_H