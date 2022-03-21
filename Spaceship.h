#pragma once
#include "CollidableObject.h"

#include <memory>
#include <string>


class Spaceship :
    public CollidableObject
{
public:
    Spaceship(Vector2D initPos, Vector2D vel, float rotation, float sc, bool activated, std::wstring path);
    Spaceship(Vector2D initPos, Vector2D vel, float rotation, float sc, bool activated);
    Spaceship(Vector2D initPos, Vector2D vel, float rotation);
    Spaceship(Vector2D initPos, Vector2D vel, bool activated);
    Spaceship(Vector2D initPos, Vector2D vel);
    Spaceship(Vector2D initPos);
    IShape2D& GetShape();
    Spaceship();
    ~Spaceship();

   // void Initialize();
    void Updated(float timeFrame);
    void ProcessCollision(std::shared_ptr<CollidableObject> other);
protected:
    //void Render(); 
private:
    Vector2D velocity;

    Circle2D boundingCircle;
    
    const float frictionPower = 0.5f;
    const float AccPower = 200.0f;

    const Vector2D right = Vector2D(100.0f, 0.0f);     
    const Vector2D left = Vector2D(-100.0f, 0.0f);
    const Vector2D up = Vector2D(0.0f, 100.0f);
    const Vector2D down = Vector2D(0.0f, -9.81f);

};


