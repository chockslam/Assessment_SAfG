#pragma once
#include "CollidableObject.h"
#include <list>
class Bullet :
    public CollidableObject
{

public:
    Bullet(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);
    ~Bullet() {};
    void Updated(float timeFrame);
    void ProcessCollision(std::shared_ptr<CollidableObject> other);
    IShape2D& GetShape();
private:
    Vector2D velocity;
    float timer = 2.0f; 
    Rectangle2D boundingRect;
};

