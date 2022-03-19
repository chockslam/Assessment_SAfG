#pragma once
#include "CollidableObject.h"
#include "ObjectManager.h"
class Bullet :
    public CollidableObject
{

public:
    Bullet(Vector2D initPos, Vector2D vel, float rotation, float sc, bool activated, std::wstring path);
    ~Bullet() {};
    void Updated(float timeFrame);
    void ProcessCollision(std::shared_ptr<CollidableObject> other);
    void Initialize(std::shared_ptr<ObjectManager> om);
    IShape2D& GetShape();
private:


    std::shared_ptr<ObjectManager> om;
    Vector2D velocity;
    float timer = 2.0f; 
    Rectangle2D boundingRect;
};

