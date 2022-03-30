#pragma once
#include "Character.h"
class Zombie :
    public Character
{
public:
    Zombie(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);
    void setLevel(int level);
    void Updated(float timeFrame);
    IShape2D& GetShape();
    void ProcessCollision(std::shared_ptr<CollidableObject> other);
    Vector2D getVel() const { return this->velocity; };
    virtual void ProcessProximity(std::shared_ptr<GameObject> other);
private:
    void goTo(Vector2D pos);

    int level;

    Rectangle2D boundingRect;
};

