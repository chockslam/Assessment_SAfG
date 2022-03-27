#pragma once
#include "PlayableCharacter.h"
#include <memory>
#include <string>

class Hero :
    public PlayableCharacter
{
public:
    Hero(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);
    Hero(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, bool activated);
    Hero(Vector2D initPos, Vector2D vel, float rotation);
    Hero(Vector2D initPos, Vector2D vel, bool activated);
    Hero(Vector2D initPos, Vector2D vel);
    Hero(Vector2D initPos);
    IShape2D& GetShape();
    Hero();
    ~Hero();

    Vector2D getVel() const { return this->velocity; };

    void Updated(float timeFrame);
    void ProcessCollision(std::shared_ptr<CollidableObject> other);
protected:
    //void Render(); 
private:
    Vector2D velocity;

    float invincTimer;
    Circle2D boundingCircle;
    
    const float frictionPower = 5.5f;
    const float AccPower = 200.0f;


    const Vector2D right = Vector2D(100.0f, 0.0f);     
    const Vector2D left = Vector2D(-100.0f, 0.0f);
    const Vector2D up = Vector2D(0.0f, 100.0f);
    const Vector2D down = Vector2D(0.0f, -9.81f);

};


