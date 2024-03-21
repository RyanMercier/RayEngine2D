#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include "component.h"

// Base System class
class System
{
public:
    virtual void Update(float deltaTime) = 0;
};

// Example system for updating Transforms
class MovementSystem : public System
{
private:
    std::vector<TransformComponent> &Transforms;

public:
    MovementSystem(std::vector<TransformComponent> &pos) : Transforms(pos) {}

    void Update(float deltaTime) override;
};

#endif
// SYSTEM_H