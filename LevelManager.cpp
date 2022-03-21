#include "LevelManager.h"
#include "mydrawengine.h"
#include "ObjectManager.h"
std::shared_ptr<LevelManager> LevelManager::d(new LevelManager);

LevelManager::LevelManager()
	:
	GameObject::GameObject(Vector2D(0, 0), 0, 0, false, L""),
	numEnemies(0),
	playerLives(1)
{

}

void LevelManager::StartLevel()
{
	RespawnPlayer();
	// Create 8 asteroids
	RespawnEnemies();
}

void LevelManager::Initialize()
{

}



void LevelManager::Updated(float timeFrame)
{

	if (playerLives == 0) {
		RespawnPlayer();
		playerLives = 1;
	}
	if (numEnemies == 0) {
		RespawnEnemies();
	}
}

void LevelManager::Render()
{

	MyDrawEngine::GetInstance()->WriteInt(50, 50, numEnemies,
		MyDrawEngine::GREEN);
	MyDrawEngine::GetInstance()->WriteInt(150, 50, playerLives,
		MyDrawEngine::GREEN);
}

void LevelManager::RespawnEnemies()
{
	for (int i = 1; i <= 10; i++) {
		ObjectManager::getInstance().Add(L"Random Flying Asteroid");
		numEnemies = i;
	}
}

void LevelManager::RespawnPlayer()
{
	ObjectManager::getInstance().Add(L"Ship", { -1000.0f, 0.0f }, { 0.0f, 0.0f }, 3.14f / 2.0f, 3.5f, 1);
}

void LevelManager::AddScore()
{
	this->score++;
}

void LevelManager::EnemyDead()
{
	numEnemies--;
}

void LevelManager::PlayerDead()
{
	playerLives--;
}
