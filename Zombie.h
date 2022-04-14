/*
    * Zombie .h file
    * 19012503
    * Aim of the class:		Represents an Enemy - Zombie. Zombie can be WEAK, NORMAL,HARD.
*/

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
    virtual void ProcessProximity(std::shared_ptr<GameObject> other, float dist, float maxDist);
private:
    void goTo(Vector2D pos);


    // level of the zombie
    int level;

    Rectangle2D boundingRect;
};

