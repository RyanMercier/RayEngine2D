#include "../headers/renderer.h"

Rectangle Renderer::GetVisibleArea()
{
    Vector2 cameraPosition;
    cameraPosition.x = camera.target.x - (camera.offset.x / camera.zoom);
    cameraPosition.y = camera.target.y - (camera.offset.y / camera.zoom);

    // Calculate visible area based on camera offset and zoom level
    Rectangle visibleArea;
    visibleArea.x = cameraPosition.x;
    visibleArea.y = cameraPosition.y;
    visibleArea.width = screenWidth / camera.zoom;
    visibleArea.height = screenHeight / camera.zoom;
    return visibleArea;
}

void Renderer::LoadTexturesFromDirectory(const char *directory)
{
    // Manually list the files in the directory
    textureFiles.push_back("resources/textures/player.png");

    for (std::string file : textureFiles)
    {
        textures[file] = LoadTexture(file.c_str());
    }
}

void Renderer::UnloadTextures()
{
    for (const auto &pair : textures)
    {
        // const std::string &key = pair.first;
        const Texture2D &texture = pair.second;
        UnloadTexture(texture);
    }
}

void Renderer::LoadTileAtlas(const char *filename)
{
    tileAtlas = LoadTexture(filename);
}

void Renderer::LoadTilemap(const char *filename, int width, int height)
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

void Renderer::UnloadTilemap()
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

void Renderer::DrawTilemap()
{
    if (tilemap != nullptr)
    {
        Rectangle visibleArea = GetVisibleArea();

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

void Renderer::DrawSprites()
{
    auto spriteInfo = game->GetSpriteInfo();
    Rectangle visibleArea = GetVisibleArea();

    for (const auto &tuple : spriteInfo)
    {
        SpriteComponent *spriteComponent = std::get<0>(tuple);
        TransformComponent *transformComponent = std::get<1>(tuple);
        AnimationComponent *animationComponent = std::get<2>(tuple); // Assuming you added AnimationComponent to the system

        if (transformComponent && spriteComponent)
        {
            // Check if sprite is within the visible area
            if (transformComponent->x >= visibleArea.x && transformComponent->x <= visibleArea.x + visibleArea.width &&
                transformComponent->y >= visibleArea.y && transformComponent->y <= visibleArea.y + visibleArea.height)
            {
                // If AnimationComponent is available, update the sourceRect
                if (animationComponent)
                {
                    std::cout << "update called" << std::endl;
                    animationComponent->Update(GetFrameTime());
                    spriteComponent->sourceRect = animationComponent->GetCurrentFrame();
                }

                // Draw the texture using the sourceRect for animations
                DrawTextureRec(textures[spriteComponent->spritePath],
                               spriteComponent->sourceRect,
                               {static_cast<float>(static_cast<int>(transformComponent->x)),
                                static_cast<float>(static_cast<int>(transformComponent->y))},
                               WHITE);
            }
        }
    }
}