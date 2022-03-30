#pragma once
#include "UIElement.h"
class EndScreen :
    public UIElement
{
public:
    EndScreen(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);
    void Updated(float timeFrame);
    void Initialize();
    //void Render();
private:
    float duration;
};

