/*
    * Dead Screen .h file
    * 19012503
    * Aim of the class: Represents any screen displayed after the player dies.
    * DRAWBACK: Dead screen/End Screen/Start screen might be merged to reduce amount of code.
*/


#pragma once
#include "UIElement.h"
class DeadScreen :
    public UIElement
{
public:
    DeadScreen(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);
    void Updated(float timeFrame);
    void Initialize();
    void Render();
private:
    // how long would dead screen be displayed.
    float duration;
};

