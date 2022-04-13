/*
    * Character .h file
    * 19012503
    * Aim of the class: Represents any character - whether it is a player or zombie.
    * Notes :   NEEDS TO BE EXTENDED BY ACTUAL REPRESENTATION OF CHARACTERS, i.e. zombie or hero.
    *           ALL EXPLANATION REGARDING FUNCTIONS' PURPOSE IS LOCATED IN .CPP FILE.
*/

#pragma once
#include "CollidableObject.h"



class Character :
    public CollidableObject
{
protected:
    Character(Vector2D initPos, Vector2D velocity, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);

    void playAnimOnce(std::wstring animName, float timeFrame);
    void knockBack(float power, float animSpeed, std::shared_ptr<GameObject> otherObj = nullptr);
    void RestrictMovement(int minY,int minX, int maxY,int maxX, int maxCameraX = 0, int minCameraX = 0, bool trackedByCamera = false);


    Vector2D velocity;


    bool attacking;                         // whether the character is currently attacking.
    float attackTimer;                      // how much time does attack animation needs to be played once.

    bool knocked;                           // whether the character is currently stunned/knocked.
    float knockedTimer;                     // how much time does attack animation needs to be played once.

    int deathSound;                         // play this sound if dead.
    int hurtSound;                          // play this sound if damaged.

    float health;                           // health of the character
    const float AccPower = 200.0f;          // movement related parameter
    float frictionPower;                    // movement related parameter
};

