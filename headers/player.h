#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Actor
{
public:
    Player(float xPos, float yPos)
    {
        AddComponent<TransformComponent>(xPos, yPos);
        AddComponent<SpriteComponent>("resources/textures/player.png");

        // Add the AnimationComponent and store the pointer to it
        auto *animationComponent = AddComponent<AnimationComponent>(0.1f); // Frame duration: 0.1s

        // Define the frames for the "walk" animation
        std::vector<Rectangle> walkFrames = {
            {0, 0, 32, 32},  // Frame 1
            {32, 0, 32, 32}, // Frame 2
            {64, 0, 32, 32}, // Frame 3
            // Add more frames as needed
        };

        // Add the "walk" animation and set it as the current animation
        animationComponent->AddAnimation("walk", walkFrames);
        animationComponent->SetAnimation("walk");
    }
};

#endif