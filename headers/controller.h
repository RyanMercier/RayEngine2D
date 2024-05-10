#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <raylib.h>
#include <vector>
#include "command.h"
#include "game.h"

class Controller
{
private:
    Camera2D *camera;
    Game *game;
    std::vector<Command *> commands; // Vector to store commands
    float cameraSpeed = 200.0f;

public:
    Controller(Camera2D *cam, Game *gme) : camera(cam), game(gme)
    {
    }

    ~Controller()
    {
        // Cleanup commands
        for (Command *cmd : commands)
        {
            delete cmd;
        }
    }

    void Update(float deltaTime)
    {
        // Clear commands from previous frame
        commands.clear();

        // Handle camera movement commands
        if (IsKeyDown(KEY_D))
        {
            commands.push_back(new MoveEntityCommand(game->GetPlayer(), cameraSpeed * deltaTime, 0.0f));
        }
        if (IsKeyDown(KEY_A))
        {
            commands.push_back(new MoveEntityCommand(game->GetPlayer(), -cameraSpeed * deltaTime, 0.0f));
        }
        if (IsKeyDown(KEY_S))
        {
            commands.push_back(new MoveEntityCommand(game->GetPlayer(), 0.0f, cameraSpeed * deltaTime));
        }
        if (IsKeyDown(KEY_W))
        {
            commands.push_back(new MoveEntityCommand(game->GetPlayer(), 0.0f, -cameraSpeed * deltaTime));
        }

        TransformComponent *playerPos = game->GetPlayer()->GetComponents<TransformComponent>()[0];
        camera->target = {playerPos->x, playerPos->y};

        // std::cout << playerPos->x << ", " << playerPos->y << std::endl;

        // Handle zooming commands
        if (IsKeyDown(KEY_Z))                                         // For example, you can use the Z key for zooming in
            commands.push_back(new ZoomCameraCommand(camera, 0.1f));  // Zoom in
        if (IsKeyDown(KEY_X))                                         // For example, you can use the X key for zooming out
            commands.push_back(new ZoomCameraCommand(camera, -0.1f)); // Zoom out

        // Handle shooting command
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            commands.push_back(new ShootCommand(game));
        }

        // Execute all commands
        for (Command *cmd : commands)
        {
            cmd->Execute();
        }
    }
};

#endif
// CONTROLLER_H