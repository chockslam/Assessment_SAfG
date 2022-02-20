#pragma once
#include "GameObject.h"

#include <string>

class Spaceship :
    public GameObject
{
public:
    Spaceship(Vector2D initPos, Vector2D vel, float rotation, bool activated, std::wstring path);
    Spaceship(Vector2D initPos, Vector2D vel, float rotation, bool activated);
    Spaceship(Vector2D initPos, Vector2D vel, float rotation);
    Spaceship(Vector2D initPos, Vector2D vel, bool activated);
    Spaceship(Vector2D initPos, Vector2D vel);
    Spaceship(Vector2D initPos);
    Spaceship();

   // void Initialize();
    void Updated();

protected:
    //void Render();
private:
    Vector2D velocity;

    float posOffsetPower = 1.0f;

    const Vector2D right = Vector2D(4.0f, 0.0f);
    const Vector2D left = Vector2D(-4.0f, 0.0f);
    const Vector2D up = Vector2D(0.0f, 4.0f);
    const Vector2D down = Vector2D(4.0f, -4.0f);

};


