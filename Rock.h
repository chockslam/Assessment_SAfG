#pragma once
#include "GameObject.h"
class Rock :
    public GameObject
{
public:
    Rock(Vector2D initPos, Vector2D vel, float rotation, bool activated, std::wstring path);
    void Updated(float timeFrame);
};

