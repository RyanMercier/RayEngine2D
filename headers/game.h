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
    Actor *CreateActor()
    {
        Actor *actor = new Actor();
        // Add default components for Actors
        actor->AddComponent<TransformComponent>();
        actor->AddComponent<PhysicsComponent>();
        // Add actor to ECS
        entityComponentMap[actor->GetId()] = actor->GetAllComponents();
        return actor;
    }

    Item *CreateItem()
    {
        Item *item = new Item();
        // Add default components for Items
        item->AddComponent<TransformComponent>();
        // Add item to ECS
        entityComponentMap[item->GetId()] = item->GetAllComponents();
        return item;
    }

    Prop *CreateProp()
    {
        Prop *prop = new Prop();
        // Add default components for Props
        prop->AddComponent<TransformComponent>();
        // Add prop to ECS
        entityComponentMap[prop->GetId()] = prop->GetAllComponents();
        return prop;
    }

    void Shoot()
    {
    }

    void Update(float deltaTime)
    {
    }
};

#endif