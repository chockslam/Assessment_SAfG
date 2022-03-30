#pragma once
#include "GameObject.h"
class UIElement :
    public GameObject
{
public:
    UIElement(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);
    virtual void Render();
protected:
    Vector2D localPosition;
};

