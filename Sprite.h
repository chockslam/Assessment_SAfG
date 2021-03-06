/*
    * Sprite .h file
    * 19012503
    * Aim of the class:		Represents any non-collidable sprite in the game world, i.e. background, foreground, etc.
*/

#pragma once
#include "GameObject.h"
#include <list>



class Sprite :
    public GameObject
{
public:
    Sprite(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);
    ~Sprite() {};
    void Updated(float timeFrame);
    void repeatOn(bool flag, float customSpeed = 0.2f);
};

