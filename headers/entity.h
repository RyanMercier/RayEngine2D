#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "component.h" // Include Component definitions

// Base Entity class
class Entity
{
private:
    static int nextId;
    int id;
    std::vector<Component *> components;

public:
    Entity() : id(nextId++) {}
    virtual ~Entity()
    {
        // Clean up components
        for (Component *comp : components)
        {
            delete comp;
        }
    }

    int GetId() const { return id; }

    // Add a component to the entity
    template <typename T, typename... Args>
    void AddComponent(Args &&...args)
    {
        components.push_back(new T(std::forward<Args>(args)...));
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
    std::vector<Component *> components; // Components associated with Actors

public:
    Actor() {}
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
    std::vector<Component *> components; // Components associated with Items

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
    std::vector<Component *> components; // Components associated with Props

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