/*
    * Start Screen .h file
    * 19012503
    * Aim of the class: Represents any screen displayed before the level starts.
    * DRAWBACK: Dead screen/End Screen/Start screen might be merged to reduce amount of code.
*/


#pragma once
#include "UIElement.h"
class StartScreen :
    public UIElement
{
public:
    StartScreen(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);
    void Updated(float timeFrame);
    void Initialize();
private:
    float duration;
};

