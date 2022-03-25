#pragma once
#include "CollidableObject.h"
class Character :
    public CollidableObject
{
protected:
    Character(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);

    bool knocked;
    float knockedTimer;
    float health;
};

