#include "../headers/system.h"

void MovementSystem::Update(float deltaTime)
{
    // Iterate over TransformComponents and update Transforms
    for (TransformComponent &pos : Transforms)
    {
        // Update Transform based on velocity, etc.
    }
}