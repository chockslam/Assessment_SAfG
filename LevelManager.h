#pragma once
#include "GameObject.h"

#include <list>;
#include <vector>;

class LevelManager :
    public GameObject
{
public:

    static std::shared_ptr<LevelManager> getInstance() {
        if (!d)
            d.reset(new LevelManager);
        return d;
    }

    void StartLevel();
    void Initialize();
    void Updated(float timeFrame);
    void Render();
    
    void AddScore();
    void EnemyDead();
    void PlayerDead();
    int getMinY() const { return minY; };
    int getMaxY() const { return maxY; };
    void SetYPos(int Ypos);
    void SetHP(int hp);
    void SetMaxHP(int hp);
    float getHeroHealth() const { return heroHealth; };
    float getMaxHeroHealth() const { return maxHeroHealth; };


private:

    void makeUI();
    void CreateBackground(int length);
    void CreateForeground(int length);

    void RespawnEnemies();
    void RespawnPlayer();
    
    LevelManager();
    static std::shared_ptr<LevelManager> d;
    
    int YPos;
    int maxY;
    int minY;

    int level;
    int currentLevel;
    
    int score;
    int endTimer;

    int heroHealth;
    int maxHeroHealth;
    int numEnemies;
    int playerLives; 
};

