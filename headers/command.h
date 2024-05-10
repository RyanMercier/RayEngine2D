#ifndef COMMAND_H
#define COMMAND_H

#include <raylib.h>
#include "game.h"

class Command
{
public:
    virtual ~Command() {}
    virtual void Execute() = 0;
};

// CAMERA COMMANDS
class MoveCameraCommand : public Command
{
private:
    Camera2D *camera;
    Vector2 offset;

public:
    MoveCameraCommand(Camera2D *cam, const Vector2 &offset) : camera(cam), offset(offset) {}

    void Execute() override
    {
        camera->offset.x += offset.x;
        camera->offset.y += offset.y;
    }
};

class ZoomCameraCommand : public Command
{
private:
    Camera2D *camera;
    float zoomDelta;

public:
    ZoomCameraCommand(Camera2D *cam, float delta) : camera(cam), zoomDelta(delta) {}

    void Execute() override
    {
        camera->zoom += zoomDelta;

        // Clamp zoom within reasonable bounds
        if (camera->zoom > 3.0f)
            camera->zoom = 3.0f;
        else if (camera->zoom < 0.2f)
            camera->zoom = 0.2f;
    }
};

class ShootCommand : public Command
{
private:
    Game *game;

public:
    ShootCommand(Game *gme) : game(gme) {}

    void Execute() override
    {
        game->Shoot();
    }
};

// Entity COMMANDS
class MoveEntityCommand : public Command
{
private:
    Entity *entity;
    float xOffset = 0;
    float yOffset = 0;

public:
    MoveEntityCommand(Entity *e, float xOffset, float yOffset)
    {
        entity = e;
        this->xOffset = xOffset;
        this->yOffset = yOffset;
    }

    void Execute() override
    {
        TransformComponent *transform = entity->GetComponents<TransformComponent>()[0];
        transform->x += xOffset;
        transform->y += yOffset;
    }
};

class SetEntityLocationCommand : public Command
{
private:
    Entity *entity;
    float xPos = 0;
    float yPos = 0;

public:
    SetEntityLocationCommand(Entity *e, float xPos, float yPos)
    {
        entity = e;
        this->xPos = xPos;
        this->yPos = yPos;
    }

    void Execute() override
    {
        TransformComponent *transform = entity->GetComponents<TransformComponent>()[0];
        transform->x = xPos;
        transform->y = yPos;
    }
};

#endif
// COMMAND_H