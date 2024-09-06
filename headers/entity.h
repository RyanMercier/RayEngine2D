#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "raylib.h"
#include "component.h" // Include Component definitions

// Base Entity class
class Entity
{
protected:
    static int nextId;
    int id;
    std::vector<Component *> components;

public:
    Entity() : id(nextId++)
    {
    }

    virtual ~Entity()
    {
        // Clean up components
        for (Component *comp : components)
        {
            delete comp;
        }
    }

    int GetId() const { return id; }

    // Add a component to the entity and return a pointer to it
    template <typename T, typename... Args>
    T *AddComponent(Args &&...args)
    {
        T *component = new T(std::forward<Args>(args)...);
        components.push_back(component);
        return component;
    }

    // Get components of a specific type
    template <typename T>
    std::vector<T *> GetComponents() const
    {
        std::vector<T *> result;
        for (Component *comp : components)
        {
            if (T *castedComp = dynamic_cast<T *>(comp))
            {
                result.push_back(castedComp);
            }
        }
        return result;
    }

    // Get all components associated with the entity
    std::vector<Component *> GetAllComponents() const
    {
        return components;
    }

    // Update method to be overridden by subclasses
    virtual void Update(float deltaTime) = 0;
};

// Actor class inheriting from Entity
class Actor : public Entity
{
protected:
public:
    Actor() {}

    Actor(float xPos, float yPos)
    {
        AddComponent<TransformComponent>(xPos, yPos);
    }

    virtual ~Actor()
    {
        // Cleanup components
        for (Component *comp : components)
        {
            delete comp;
        }
    }

    // Override Update method for Actors
    void Update(float deltaTime) override;
};

// Item class inheriting from Entity
class Item : public Entity
{
protected:
public:
    Item() {}
    virtual ~Item()
    {
        // Cleanup components
        for (Component *comp : components)
        {
            delete comp;
        }
    }

    // Override Update method for Items
    void Update(float deltaTime) override;
};

// Prop class inheriting from Entity
class Prop : public Entity
{
protected:
public:
    Prop() {}
    virtual ~Prop()
    {
        // Cleanup components
        for (Component *comp : components)
        {
            delete comp;
        }
    }

    // Override Update method for Props
    void Update(float deltaTime) override;
};

#endif
// ENTITY_H