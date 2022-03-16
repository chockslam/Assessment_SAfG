#pragma once
#include "GameObject.h"
class Bullet :
    public GameObject
{

public:
    Bullet(Vector2D initPos, Vector2D vel, float rotation, float sc, bool activated, std::wstring path);
    void Updated(float timeFrame);
    IShape2D& GetShape();
private:
    Vector2D velocity;
    float timer = 2.0f; 
    Circle2D boundingCircle;
};

