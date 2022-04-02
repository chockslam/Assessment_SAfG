#pragma once
#include "UIElement.h"
class HealthBar :
    public UIElement
{
public:
    HealthBar(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);
    void Updated(float timeFrame);
private:
    float initScaleX;
    float maxHealth;
    float currHealth;
};
