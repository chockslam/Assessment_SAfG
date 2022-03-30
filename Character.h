#pragma once
#include "CollidableObject.h"
class Character :
    public CollidableObject
{
protected:
    Character(Vector2D initPos, Vector2D velocity, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);

    void playAnimOnce(std::wstring animName, float timeFrame);
    void knockBack(float power, float animSpeed, std::shared_ptr<GameObject> otherObj = nullptr);


    Vector2D velocity;

    bool attacking;
    float attackTimer;

    bool knocked;
    float knockedTimer;

    float health;
    const float AccPower = 200.0f;
    float frictionPower;
};

