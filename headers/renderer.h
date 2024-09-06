#ifndef RENDERER_H
#define RENDERER_H

#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include "raylib.h"
#include "../headers/game.h"
#include "../headers/component.h"

class Renderer
{
protected:
    int screenWidth;
    int screenHeight;
    int tileSize;
    int **tilemap;
    Texture2D tileAtlas;
    std::unordered_map<std::string, Texture2D> textures;
    Shader shader;
    std::vector<std::string> textureFiles;
    Camera2D camera; // Raylib's built-in Camera2D struct
    Game *game;

public:
    Renderer(int width, int height, int size)
    {
        screenWidth = width;
        screenHeight = height;
        tileSize = size;
        tilemap = nullptr;
    }

    ~Renderer()
    {
        UnloadTextures();
        UnloadTilemap();
        UnloadShader(shader);
    }

    void Init(Game *game)
    {
        this->game = game;
        LoadTexturesFromDirectory("");
        LoadTileAtlas("resources/textures/palette.png"); // Load the palette texture
        LoadTilemap("resources/tilemap.txt", screenWidth / tileSize, screenHeight / tileSize);
        shader = LoadShader("shaders/vert.glsl", "shaders/frag.glsl");

        // Initialize the camera
        camera.target = Vector2{0, 0};
        camera.offset = Vector2{screenWidth / 2.0f, screenHeight / 2.0f};
        camera.rotation = 0.0f;
        camera.zoom = 1.5f;
    }

    Camera2D &GetCamera()
    {
        return camera;
    }

    Rectangle GetVisibleArea();

    void LoadTexturesFromDirectory(const char *directory);

    void UnloadTextures();

    void LoadTileAtlas(const char *filename);

    void LoadTilemap(const char *filename, int width, int height);

    void UnloadTilemap();

    void Draw()
    {
        BeginShaderMode(shader);
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);

        DrawTilemap();
        DrawSprites();

        EndMode2D();

        EndDrawing();
        EndShaderMode();
    }

private:
    void DrawTilemap();
    void DrawSprites();
};

#endif
// RENDERER_H