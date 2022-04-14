/*
    * UIElement .h file
    * 19012503
    * Aim of the class: Represents any UI Element.
    *                   It has a specific Render function that allows rendering 'on the camera screen'
*/


#pragma once
#include "GameObject.h"
class UIElement :
    public GameObject
{
public:
    UIElement(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);
    virtual void Render();
protected:
    // position on the screen.
    Vector2D localPosition;
};

