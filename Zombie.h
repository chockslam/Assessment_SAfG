#pragma once
#include "CollidableObject.h"
class Zombie :
    public CollidableObject
{
public:
    Zombie(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);
    void Updated(float timeFrame);
    IShape2D& GetShape();
    void ProcessCollision(std::shared_ptr<CollidableObject> other);
    Vector2D getVel() const { return this->velocity; };
    virtual void ProcessProximity(std::shared_ptr<GameObject> other);
private:
    void goTo(Vector2D pos);

    Vector2D velocity;
    Rectangle2D boundingRect;
};

