#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
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
    void Initialize(std::shared_ptr<ObjectManager> om);
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

    int currentLevel;
    int score;
    int endTimer;
    int numEnemies;
    int playerLives; 
    std::shared_ptr<ObjectManager> om; 
};

