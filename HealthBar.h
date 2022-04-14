/*
    * Healthbar .h file
    * 19012503
    * Aim of the class:		Reprsents health bar located on the top of the screen. 
*/

#pragma once
#include "UIElement.h"
class HealthBar :
    public UIElement
{
public:
    HealthBar(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);
    void Updated(float timeFrame);
private:
    // variables needed for calulculation of the length of the health bar using proportion mechanism
    float initScaleX;
    float maxHealth;
    float currHealth;
};
