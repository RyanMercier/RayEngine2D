#include "../headers/game.h"

Player *Game::CreatePlayer()
{
    Player *player = new Player(100.0f, 100.0f);
    // Add default components for Actors
    // Add actor to ECS
    entityComponentMap[player->GetId()] = player->GetAllComponents();
    return player;
}

Actor *Game::CreateActor()
{
    Actor *actor = new Actor(100.0f, 100.0f);
    // Add default components for Actors
    // Add actor to ECS
    entityComponentMap[actor->GetId()] = actor->GetAllComponents();
    return actor;
}

Item *Game::CreateItem()
{
    Item *item = new Item();
    // Add item to ECS
    entityComponentMap[item->GetId()] = item->GetAllComponents();
    return item;
}

Prop *Game::CreateProp()
{
    Prop *prop = new Prop();
    // Add prop to ECS
    entityComponentMap[prop->GetId()] = prop->GetAllComponents();
    return prop;
}

void Game::Update(float deltaTime)
{
    // Update each system
    for (auto &system : systems)
    {
        system->Update(deltaTime);
    }
}