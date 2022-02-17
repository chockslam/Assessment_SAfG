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

    void Initialize();
    void Updated();

protected:
    void Render();
private:
    std::wstring path;
    int image;
    Vector2D velocity;
};


