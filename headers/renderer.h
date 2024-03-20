#ifndef RENDERER_H
#define RENDERER_H

#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include "raylib.h"

class Renderer
{
private:
    int screenWidth;
    int screenHeight;
    int tileSize;
    int **tilemap;
    Texture2D tileAtlas;
    Texture2D *textures;
    int texturesCount;
    Shader shader;
    std::vector<std::string> textureFiles;
    Camera2D camera; // Raylib's built-in Camera2D struct

public:
    Renderer(int width, int height, int size)
    {
        screenWidth = width;
        screenHeight = height;
        tileSize = size;
        tilemap = nullptr;
        textures = nullptr;
        texturesCount = 0;
    }

    ~Renderer()
    {
        UnloadTextures();
        UnloadTilemap();
        UnloadShader(shader);
    }

    void Init()
    {
        // LoadTexturesFromDirectory("textures"); // Assuming textures are stored in a "textures" directory
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

    void LoadTexturesFromDirectory(const char *directory)
    {
        // Manually list the files in the directory
        textureFiles.push_back("textures/texture1.png");
        textureFiles.push_back("textures/texture2.png");

        texturesCount = textureFiles.size();
        textures = new Texture2D[texturesCount];

        for (int i = 0; i < texturesCount; ++i)
        {
            textures[i] = LoadTexture(textureFiles[i].c_str());
        }
    }

    void UnloadTextures()
    {
        for (int i = 0; i < texturesCount; ++i)
        {
            UnloadTexture(textures[i]);
        }
        delete[] textures;
    }

    void LoadTileAtlas(const char *filename)
    {
        tileAtlas = LoadTexture(filename);
    }

    void LoadTilemap(const char *filename, int width, int height)
    {
        tilemap = new int *[width];
        for (int i = 0; i < width; ++i)
        {
            tilemap[i] = new int[height];
        }

        FILE *file = fopen(filename, "r");
        if (file != nullptr)
        {
            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width; ++x)
                {
                    char tileChar;
                    fscanf(file, " %c", &tileChar);            // Read a character, ignoring whitespace
                    tilemap[x][y] = (tileChar == '1') ? 1 : 0; // Convert character to integer
                }
            }

            fclose(file);
        }
    }

    void UnloadTilemap()
    {
        if (tilemap != nullptr)
        {
            for (int i = 0; i < screenWidth / tileSize; ++i)
            {
                delete[] tilemap[i];
            }
            delete[] tilemap;
        }
    }

    void Draw()
    {
        BeginShaderMode(shader);
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);

        DrawTilemap();

        EndMode2D();

        EndDrawing();
        EndShaderMode();
    }

private:
    void DrawTilemap()
    {
        if (tilemap != nullptr)
        {
            // Calculate visible area based on camera position and zoom level
            Rectangle visibleArea;
            visibleArea.x = -camera.offset.x / camera.zoom;
            visibleArea.y = -camera.offset.y / camera.zoom;
            visibleArea.width = screenWidth / camera.zoom;
            visibleArea.height = screenHeight / camera.zoom;

            // Calculate tile indices based on visible area
            int startX = std::max(0, static_cast<int>(visibleArea.x / tileSize));
            int startY = std::max(0, static_cast<int>(visibleArea.y / tileSize));
            int endX = std::min(screenWidth / tileSize, static_cast<int>((visibleArea.x + visibleArea.width) / tileSize) + 1);
            int endY = std::min(screenHeight / tileSize, static_cast<int>((visibleArea.y + visibleArea.height) / tileSize) + 1);

            // Draw tiles within the visible area
            for (int x = startX; x < endX; x++)
            {
                for (int y = startY; y < endY; y++)
                {
                    int atlasIndex = tilemap[x][y];
                    if (atlasIndex >= 0)
                    {
                        // Calculate the source rectangle within the palette texture
                        Rectangle sourceRect;
                        sourceRect.x = atlasIndex * tileSize;
                        sourceRect.y = 0;
                        sourceRect.width = tileSize;
                        sourceRect.height = tileSize;

                        Vector2 destPosition;
                        destPosition.x = x * tileSize;
                        destPosition.y = y * tileSize;

                        // Draw the portion of the palette texture onto the screen
                        DrawTextureRec(tileAtlas, sourceRect, destPosition, WHITE);
                    }
                }
            }
        }
    }
};

#endif