#include "LevelManager.h"
#include "mydrawengine.h"
#include "ObjectManager.h"

#define LEVEL_ONE 1
#define LEVEL_ONE_MAX_Y 492
#define LEVEL_ONE_MIN_Y -877


std::shared_ptr<LevelManager> LevelManager::d(new LevelManager);

LevelManager::LevelManager()
	:
	GameObject::GameObject(Vector2D(0, 0), 0, 0, 0, false, {}),
	numEnemies(0),
	playerLives(1),
	minY(-100000000),
	maxY(100000000)

{
	
}

void LevelManager::StartLevel()
{
	this->CreateBackground(5);
	
	RespawnPlayer();
	RespawnEnemies();



	this->CreateForeground(2);

	makeUI();
	
}

void LevelManager::Initialize()
{
	this->level = LEVEL_ONE;
	this->minY = LEVEL_ONE_MIN_Y;
	this->maxY = LEVEL_ONE_MAX_Y;
	
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
	std::list<Vector2D> list;
	ObjectManager::getInstance().checkProximity(L"Zombies", L"Player", 1000.0f);
}

void LevelManager::Render()
{

	MyDrawEngine::GetInstance()->WriteInt(50, 50, numEnemies,
		MyDrawEngine::GREEN);
	MyDrawEngine::GetInstance()->WriteInt(150, 50, playerLives,
		MyDrawEngine::GREEN);
	MyDrawEngine::GetInstance()->WriteInt(250, 50, YPos,
		MyDrawEngine::BLUE);
}

void LevelManager::makeUI()
{
	ObjectManager::getInstance().Add(L"Health Bar", { 0.0f , 900.0f }, { 0.0f, 0.0f }, 0.0f, 4.0f);
}

void LevelManager::CreateBackground(int length)
{
	float size = 2048.0f;				// hardcoded. Should be dependent on the width of the picture
	float widthScale = 2.0f;			// hardcoded
	for (int i = 0; i < length; i++) {
		ObjectManager::getInstance().Add(L"Dungeon Background", { -250.0f + size * i * widthScale, 0.0f }, { 0.0f, 0.0f }, 0.0f, widthScale, 2.0f, 1);
	}
}

void LevelManager::CreateForeground(int length)
{
	float size = 2048.0f;				// hardcoded. Should be dependent on the width of the picture
	float widthScale = 5.0f;			// hardcoded
	for (int i = 0; i < length; i++) {
		ObjectManager::getInstance().Add(L"Fog", { -250.0f + size * i *widthScale, 0.0f }, { 0.0f, 0.0f }, 0.0f, widthScale, 9.0f, 1);
	}
}

void LevelManager::RespawnEnemies()
{
	for (int i = 1; i <= 10; i++) {
		ObjectManager::getInstance().Add(L"Normal Zombie", Vector2D(i * 100.0f, 300.0f), {}, 0.0f, 3.5f, 3.5f,1);
		ObjectManager::getInstance().Add(L"Normal Crawler", Vector2D(i * 100.0f, 0.0f), {}, 0.0f, 3.5f, 3.5f,2);
		numEnemies = i;
	}
}

void LevelManager::RespawnPlayer()
{
	ObjectManager::getInstance().Add(L"Player", { -1000.0f, 0.0f }, { 0.0f, 0.0f }, 4.5f, 4.5f, 0.0f, 1);
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

void LevelManager::SetYPos(int Ypos)
{
	this->YPos = Ypos;
}

void LevelManager::SetHP(int hp)
{
	this->heroHealth = hp;
}

void LevelManager::SetMaxHP(int hp)
{
	this->maxHeroHealth = hp;
}
