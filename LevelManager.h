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
    //static std::shared_ptr<LevelManager> getInstance() {
    //    if (!d)
    //        d.reset(new LevelManager);
    //    return d;
    //}

    void StartLevel(int level = 1);
    void Initialize();
    void Updated(float timeFrame);
    void Render();
    
    void AddScore();
    void EnemyDead();
    void PlayerDead();

    void SetYPos(int Ypos);
    void SetXPos(int Xpos);
    void SetHP(int hp);
    void SetMaxHP(int hp);

    float getHeroHealth() const { return heroHealth; };
    float getMaxHeroHealth() const { return maxHeroHealth; };
    int getMinY() const { return minY; };
    int getMaxY() const { return maxY; };

    int getMinCameraX() const { return minX; };
    int getMaxCameraX() const { return maxX; };
    
    int getMinPlayerX() const { return minX - PLAYER_OFFSET_X; };
    int getMaxPlayerX() const { return maxX + PLAYER_OFFSET_X; };

    float getDeathCoolDown() const { return playerDeathCoolDownTimer; };
    float getStartTimer() const { return startGameTimer; };
    float getEndTimer() const { return endGameTimer; };



private:

    void makeUI();
    void CreateBackground(int length);
    void CreateForeground(int length);

    void RespawnEnemies();
    void RespawnPlayer();
    
    //static std::shared_ptr<LevelManager> d;
    
    int YPos;
    int maxY;
    int minY;
    int XPos;
    int maxX;
    int minX;

    int level;
    int currentLevel;
    
    int score;
    int playerDeathCoolDownTimer;
    int startGameTimer;
    int endGameTimer;
    bool isAction;

    float maxReach;

    int heroHealth;
    int maxHeroHealth;
    int numEnemies;
    int playerLives; 
};

