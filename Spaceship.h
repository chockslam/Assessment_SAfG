#pragma once
#include "GameObject.h"

#include "mydrawengine.h"
#include <string>
class Spaceship :
    public GameObject
{
public:
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
    const wchar_t* path = L"assets\\ship.bmp";
    PictureIndex image;
    Vector2D velocity;
};


