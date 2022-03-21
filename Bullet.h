#pragma once
#include "CollidableObject.h"
class Bullet :
    public CollidableObject
{

public:
    Bullet(Vector2D initPos, Vector2D vel, float rotation, float sc, bool activated, std::wstring path);
    ~Bullet() {};
    void Updated(float timeFrame);
    void ProcessCollision(std::shared_ptr<CollidableObject> other);
    IShape2D& GetShape();
private:
    Vector2D velocity;
    float timer = 2.0f; 
    Rectangle2D boundingRect;
};

