#include "../headers/game.h"

Actor *Game::CreateActor()
{
    Actor *actor = new Actor();
    // Add default components for Actors
    actor->AddComponent<TransformComponent>();
    actor->AddComponent<PhysicsComponent>();
    // Add actor to ECS
    entityComponentMap[actor->GetId()] = actor->GetAllComponents();
    return actor;
}

Item *Game::CreateItem()
{
    Item *item = new Item();
    // Add default components for Items
    item->AddComponent<TransformComponent>();
    // Add item to ECS
    entityComponentMap[item->GetId()] = item->GetAllComponents();
    return item;
}

Prop *Game::CreateProp()
{
    Prop *prop = new Prop();
    // Add default components for Props
    prop->AddComponent<TransformComponent>();
    // Add prop to ECS
    entityComponentMap[prop->GetId()] = prop->GetAllComponents();
    return prop;
}

void Game::Update(float deltaTime)
{
}