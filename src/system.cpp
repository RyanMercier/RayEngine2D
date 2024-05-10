#include "../headers/system.h"
#include <iostream>

void MovementSystem::Update(float deltaTime)
{
    // Iterate over TransformComponents and update Transforms
    for (TransformComponent &pos : Transforms)
    {
        std::cout << pos.x << ", " << pos.y << std::endl;
    }
}