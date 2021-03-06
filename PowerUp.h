/*
    * Power-up .h file
    * 19012503
    * Aim of the class:		Represents a power-up which supposed to grant player an ability on collision.
*/

#pragma once
#include "CollidableObject.h"
class PowerUp :
    public CollidableObject
{
public:
    PowerUp(Vector2D initPos, Vector2D velocity, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);
    void Updated(float timeFrame);
    void ProcessCollision(std::shared_ptr<CollidableObject> other);
    IShape2D& GetShape();
private:
    Circle2D boundingCircle;

};

