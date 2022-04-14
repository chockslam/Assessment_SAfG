/*
    * Playable Character .h file
    * 19012503
    * Aim of the class:		Represents a controllable (by keyboard/controller) character.
    *                       Abstract Class.
*/
#pragma once
#include "Character.h"
#include "myinputs.h"
class PlayableCharacter :
    public Character
{
protected:
    PlayableCharacter(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);
    // needs to implemented by Hero.
    virtual void control(float timeFrame,int up = DIK_W, int left = DIK_A, int down = DIK_S, int right = DIK_D, int run = DIK_LSHIFT, int shoot = DIK_SPACE) = 0;
    float maxHealth;
    int fireSound;
    int poweredSound;
};

