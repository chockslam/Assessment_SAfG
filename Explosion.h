#pragma once
#include "GameObject.h"
#include <list>



class Explosion :
    public GameObject
{
public:
    Explosion(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);
    ~Explosion() {};
    void Updated(float timeFrame);
};

