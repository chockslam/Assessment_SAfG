#pragma once
#include "CollidableObject.h"
class Asteroid :
    public CollidableObject
{
public:
    Asteroid(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);
    void Updated(float timeFrame);
    IShape2D& GetShape();
    void ProcessCollision(std::shared_ptr<CollidableObject> other);
private:
    Vector2D velocity;
    Circle2D boundingCircle;
};

