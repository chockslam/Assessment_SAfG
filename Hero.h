/*
    * Hero .h file
    * 19012503
    * Aim of the class:		Represents a playable hero, who is tracked by camera and controlled using keyboard.
*/
#pragma once
#include "PlayableCharacter.h"
#include <memory>
#include <string>

class Hero :
    public PlayableCharacter
{
public:
// ---------- CONTRUCTORS WRITTEN FOR EXPERIMENTATION PURPOSES ------------------------------------------------------------------//
    Hero(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);
    Hero(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, bool activated);
    Hero(Vector2D initPos, Vector2D vel, float rotation);
    Hero(Vector2D initPos, Vector2D vel, bool activated);
    Hero(Vector2D initPos, Vector2D vel);
    Hero(Vector2D initPos);
    Hero();
// ---------- CONTRUCTORS WRITTEN FOR EXPERIMENTATION PURPOSES ------------------------------------------------------------------//
    
    IShape2D& GetShape();
    ~Hero();

    void Initialize();
    void Updated(float timeFrame);
    void ProcessCollision(std::shared_ptr<CollidableObject> other);
protected:
    // control handle
    void control(float timeFrame, int up = DIK_W, int left = DIK_A, int down = DIK_S, int right = DIK_D, int run = DIK_LSHIFT, int shoot = DIK_SPACE);
private:

    // facilitates the timer which indicates invincibility of a hero after being hit.
    float invincTimer;

    // collision detection facility
    Circle2D boundingCircle;
    
    // indicates how long does the player emits STRONG BULLETS/FIREBALLS
    float poweredUpTimer;

    // reduce frequency of shooting - timer
    float shootCoolDown;

    // facilitates varied speed of movements.
    float posOffsetPower;
};


