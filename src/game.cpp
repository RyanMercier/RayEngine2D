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

std::vector<std::tuple<SpriteComponent *, TransformComponent *, AnimationComponent *>> Game::GetSpriteInfo()
{
    std::vector<std::tuple<SpriteComponent *, TransformComponent *, AnimationComponent *>> spriteInfo;

    for (const auto &pair : entityComponentMap)
    {
        SpriteComponent *spriteComponent = nullptr;
        TransformComponent *transformComponent = nullptr;
        AnimationComponent *animationComponent = nullptr;

        for (Component *component : pair.second)
        {
            if (component->getType() == "sprite")
            {
                spriteComponent = static_cast<SpriteComponent *>(component);
            }
            else if (component->getType() == "transform")
            {
                transformComponent = static_cast<TransformComponent *>(component);
            }
            else if (component->getType() == "animation")
            {
                animationComponent = static_cast<AnimationComponent *>(component);
            }

            if (spriteComponent && transformComponent && animationComponent)
            {
                break; // Early exit if we found the required components
            }
        }

        if (spriteComponent && transformComponent)
        {
            spriteInfo.emplace_back(spriteComponent, transformComponent, animationComponent);
        }
    }

    return spriteInfo;
}