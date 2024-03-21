#include <raylib.h>
#include "../headers/renderer.h"
#include "../headers/controller.h"

const int screenWidth = 800;
const int screenHeight = 608;
const int tileSize = 32;

Renderer *renderer;
Controller *controller;
Game *game;

void Initialize()
{
    InitWindow(screenWidth, screenHeight, "RayEngine2D");
    SetTargetFPS(60);
    renderer = new Renderer(screenWidth, screenHeight, tileSize);
    renderer->Init();
    game = new Game();                                         // Initialize the Model class
    controller = new Controller(&renderer->GetCamera(), game); // Pass a pointer to the Renderer's camera to the controller
}

void Update()
{
    controller->Update(GetFrameTime());
    game->Update(GetFrameTime());
}

void Draw()
{
    renderer->Draw();
}

int main()
{
    Initialize();

    while (!WindowShouldClose())
    {
        Update();
        Draw();
    }

    CloseWindow();
    return 0;
}