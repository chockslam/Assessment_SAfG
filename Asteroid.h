#pragma once
#include "GameObject.h"
class Asteroid :
    public GameObject
{
public:
    Asteroid(Vector2D initPos, Vector2D vel, float rotation, float sc, bool activated, std::wstring path);
    void Updated(float timeFrame);
    IShape2D& GetShape();
private:
    Vector2D velocity;
    Circle2D boundingCircle;
};

