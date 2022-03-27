#pragma once
#include "Character.h"
class PlayableCharacter :
    public Character
{
protected:
    PlayableCharacter(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);
    float maxHealth;
};

