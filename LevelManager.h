#pragma once
#include "GameObject.h"

#include <list>;

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
    void RespawnEnemies();
    void RespawnPlayer();
    void AddScore();
    void EnemyDead();
    void PlayerDead();
private:

    LevelManager();
    static std::shared_ptr<LevelManager> d;
   
    Vector2D playerPos;
    
    std::list<Vector2D> velocity;

    int currentLevel;
    int score;
    int endTimer;
    int numEnemies;
    int playerLives; 
};

