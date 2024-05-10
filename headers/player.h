#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Actor
{
public:
    Player(float xPos, float yPos)
    {
        AddComponent<TransformComponent>(xPos, yPos);
    }
};

#endif