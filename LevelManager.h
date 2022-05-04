/*
    * Level Manager .h file
    * 19012503
    * Aim of the class: Manages the state of level and keeps track of levels too
    * as well as provides mechanism of communication between various objects.
    * Notes : Should be rendered and updated the last.
    * ALL EXPLANATION REGARDING FUNCTIONS' PURPOSE IS LOCATED IN .CPP FILE. 
*/

#pragma once
#include "GameObject.h"

#include <list>;
#include <vector>;

#define PLAYER_OFFSET_X 1650

class LevelManager :
    public GameObject
{
public:

    LevelManager();
    
    void StartLevel(int level = 1);
    void Initialize();
    void Updated(float timeFrame);
    void Render();
    
    void EnemyDead();
    void PlayerDead();

    void SetYPos(int Ypos);
    void SetXPos(int Xpos);
    void SetHP(int hp);
    void SetMaxHP(int hp);


    // GETTERS
    float getHeroHealth() const { return heroHealth; };                                 // Used to communicate current Hero's health to Health Bar.
    float getMaxHeroHealth() const { return maxHeroHealth; };                           // Used to communicate max Hero's health to Health Bar.
    int getMinY() const { return minY; };                                               // Area restriction related function
    int getMaxY() const { return maxY; };                                               // Area restriction related function
                                                                                        
    int getMinCameraX() const { return minX; };                                         // Area restriction related function (Camera movement)
    int getMaxCameraX() const { return maxX; };                                         // Area restriction related function (Camera movement)
                                                                                        
    int getMinPlayerX() const { return minX - PLAYER_OFFSET_X; };                       // Area restriction related function
    int getMaxPlayerX() const { return maxX + PLAYER_OFFSET_X; };                       // Area restriction related function
                                                                                        
    float getDeathCoolDown() const { return playerDeathCoolDownTimer; };                // Death screen timer
    float getStartTimer() const { return startGameTimer; };                             // Start screen timer
    float getEndTimer() const { return endGameTimer; };                                 // Level Complete screen timer



private:

    void makeUI();
    void CreateBackground(int length);
    void CreateForeground(int length);

    void RespawnEnemies();
    void RespawnPlayer();

    void RespawnPowerUps();
    
    // level building utility
    int YPos;
    
    // Level restriction regarding Y axis
    int maxY;
    int minY;
    
    // level building utility
    int XPos;
    
    // Level restriction regarding X axis
    int maxX;
    int minX;

    // current level
    int level;
    
    // Timers
    float playerDeathCoolDownTimer;
    float startGameTimer;
    float endGameTimer;
    
    // Zombies field of vision (how far away they notice you from, which also depends on the difficulty of zombie)
    float maxReach;

    // Time restriction for level. If time runs out - start game over again.
    float levelTimer;
    
    // Hero health - helps to communicate health between hero and health bar.
    int heroHealth;
    int maxHeroHealth;
    
    
    int numEnemies;             // Number of enemies.
    int playerLives;            // Must be 1 according to the logic of levels.

    int mainSong;               // Main song variable.
};

