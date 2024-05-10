#ifndef COMPONENT_H
#define COMPONENT_H

// Base Component class
class Component
{
public:
    virtual ~Component() {}
};

// Example component
class TransformComponent : public Component
{
public:
    float x, y;
    TransformComponent(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
};

// Example component
class PhysicsComponent : public Component
{
    float x, y;
};

#endif
// COMPONENT_H