#include "LevelManager.h"
#include "mydrawengine.h"

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

void LevelManager::Initialize(std::shared_ptr<ObjectManager> om)
{
	this->om = om;
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
		om->Add(L"Random Flying Asteroid");
		numEnemies = i;
	}
}

void LevelManager::RespawnPlayer()
{
	om->Add(L"Ship", { -1000.0f, 0.0f }, { 0.0f, 0.0f }, 3.14f / 2.0f, 3.5f, 1, om);
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
