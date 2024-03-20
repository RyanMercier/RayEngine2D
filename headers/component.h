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
    float x, y;
};

// Example component
class PhysicsComponent : public Component
{
    float x, y;
};

#endif