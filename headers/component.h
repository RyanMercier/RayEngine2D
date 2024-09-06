#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <unordered_map>
#include <iostream>
#include "raylib.h"

// Base Component class
class Component
{
protected:
    std::string type;

public:
    virtual ~Component() {}

    std::string getType()
    {
        return type;
    }
};

class SpriteComponent : public Component
{
public:
    std::string spritePath; // Path to the texture
    Rectangle sourceRect;   // Portion of the texture to draw (for animations)

    SpriteComponent(const std::string &path)
    {
        type = "sprite";
        spritePath = path;
        sourceRect = {0, 0, 32, 32};
    }
};

class AnimationComponent : public Component
{
public:
    std::unordered_map<std::string, std::vector<Rectangle>> animations; // Map of animation names to frame rectangles
    std::string currentAnimation;
    float frameTime;
    float elapsedTime = 0.0f;
    int currentFrame = 0;

    AnimationComponent(float frameTime) : frameTime(frameTime)
    {
        type = "animation";
    }

    void AddAnimation(const std::string &name, const std::vector<Rectangle> &frames)
    {
        animations[name] = frames;
        std::cout << "add anim" << std::endl;
    }

    void SetAnimation(const std::string &name)
    {
        if (currentAnimation != name)
        {
            currentAnimation = name;
            currentFrame = 0;
            elapsedTime = 0.0f;
        }
    }

    void Update(float deltaTime)
    {
        if (animations.find(currentAnimation) != animations.end())
        {
            elapsedTime += deltaTime;
            if (elapsedTime >= frameTime)
            {
                elapsedTime = 0.0f;
                currentFrame = (currentFrame + 1) % animations[currentAnimation].size();
                std::cout << currentFrame << std::endl;
            }
        }
    }

    Rectangle GetCurrentFrame() const
    {
        return animations.at(currentAnimation)[currentFrame];
    }
};

class TransformComponent : public Component
{
public:
    float x, y;
    TransformComponent(float x, float y)
    {
        type = "transform";
        this->x = x;
        this->y = y;
    }
};

class PhysicsComponent : public Component
{
    float x, y;
};

#endif
// COMPONENT_H