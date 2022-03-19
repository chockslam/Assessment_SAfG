#pragma once
#include "CollidableObject.h"
class Asteroid :
    public CollidableObject
{
public:
    Asteroid(Vector2D initPos, Vector2D vel, float rotation, float sc, bool activated, std::wstring path);
    void Updated(float timeFrame);
    IShape2D& GetShape();
    void ProcessCollision(std::shared_ptr<CollidableObject> other);
private:
    Vector2D velocity;
    Circle2D boundingCircle;
};

