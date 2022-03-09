#pragma once
#include "GameObject.h"
class Asteroid :
    public GameObject
{
public:
    Asteroid(Vector2D initPos, Vector2D vel, float rotation, float sc, bool activated, std::wstring path);
    void Updated(float timeFrame);
private:
    Vector2D velocity;
};

