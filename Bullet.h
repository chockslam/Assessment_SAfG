/*
    * Bullet .h file
    * 19012503
    * Aim of the class: Represent FireBall/Bullet game object.
    * ALL EXPLANATION REGARDING FUNCTIONS' PURPOSE IS LOCATED IN .CPP FILE.
*/
#pragma once
#include "CollidableObject.h"
class Bullet :
    public CollidableObject
{
public:
    Bullet(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);
    ~Bullet() {};
    void Updated(float timeFrame);
    void ProcessCollision(std::shared_ptr<CollidableObject> other);
    IShape2D& GetShape();
    void MakeStrong();              
private:
    Vector2D velocity;
    Rectangle2D boundingRect;
};

