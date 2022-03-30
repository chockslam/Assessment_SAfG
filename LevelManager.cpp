#include "LevelManager.h"
#include "mydrawengine.h"
#include "ObjectManager.h"
#include <string>

#define END_TIMER 400.0f
#define START_TIMER 100.0f
#define DEATH_COOL_DOWN_PLAYER 500.0f
#define DEATH_COOL_DOWN_SCREEN 8.0f


#define LEVEL_ONE 1
#define LEVEL_ONE_MAX_Y 492
#define LEVEL_ONE_MIN_Y -877
#define LEVEL_ONE_MAX_X 12000
#define LEVEL_ONE_MIN_X -2100


//std::shared_ptr<LevelManager> LevelManager::d(new LevelManager);

LevelManager::LevelManager()
	:
	GameObject::GameObject(Vector2D(0, 0), 0, 0, 0, false, {}),
	numEnemies(0),
	playerLives(1),
	minY(-100000000),
	maxY(100000000),
	level(1),
	playerDeathCoolDownTimer(DEATH_COOL_DOWN_PLAYER),
	screenDeathCoolDownTimer(DEATH_COOL_DOWN_SCREEN)
{
	type = ObjectType::LEVEL_MANAGER;
}

void LevelManager::StartLevel(int level)
{
	
	this->level = level;

	this->startGameTimer = START_TIMER;
	this->endGameTimer = 0.0f;

	this->CreateBackground(5);
	
	RespawnPlayer();
	RespawnEnemies();

	this->CreateForeground(2);
	

	makeUI();
	
}

void LevelManager::Initialize()
{
	this->startGameTimer = START_TIMER;
	this->endGameTimer = 0.0f;
	this->playerLives = 1;
	this->level = LEVEL_ONE;
	this->minY = LEVEL_ONE_MIN_Y;
	this->maxY = LEVEL_ONE_MAX_Y;
	this->minX = LEVEL_ONE_MIN_X;
	this->maxX = LEVEL_ONE_MAX_X;
	//ObjectManager::getInstance().Add(L"Dead Screen", { 0.0f , 0.0f }, { 0.0f, 0.0f }, 0.0f, 4.0f, 4.0f);
	
}



void LevelManager::Updated(float timeFrame)
{
	if (startGameTimer > 0.0f)
	{
		startGameTimer -= timeFrame;
	}
	else
	if (endGameTimer > 0.0f ) {
		endGameTimer -= timeFrame;
		if (endGameTimer <= 0.0f) {
			ObjectManager::getInstance().InactivateAll();
			StartLevel(++this->level);
		}
	}
	else
	{
		if (playerLives == 0) {
			if (playerDeathCoolDownTimer > 0.0f) {
				playerDeathCoolDownTimer -= timeFrame;
			}
			else {
				playerDeathCoolDownTimer = DEATH_COOL_DOWN_PLAYER;
				playerLives = 1;
				RespawnPlayer();
			}
		}
		if (numEnemies == 0) {
			endGameTimer = END_TIMER;
			ObjectManager::getInstance().Add(L"End Screen", { 0.0f , 0.0f }, { 0.0f, 0.0f }, 0.0f, 0.7f, 0.7f);
		}
	}
	

	ObjectManager::getInstance().checkOtherInteraction(L"Zombies", L"Player", 500.0f);
}

void LevelManager::Render()
{
	std::wstring textToRender = L"KILL        " + std::to_wstring(numEnemies) + L"        MORE ZOMBIES";
	MyDrawEngine::GetInstance()->WriteText(50, 40, textToRender.c_str(),
		MyDrawEngine::GREEN);
	//MyDrawEngine::GetInstance()->WriteInt(50, 50, numEnemies,
	//	MyDrawEngine::GREEN);
	//MyDrawEngine::GetInstance()->WriteInt(150, 50, playerLives,
	//	MyDrawEngine::GREEN);
	//MyDrawEngine::GetInstance()->WriteInt(250, 50, XPos,
	//	MyDrawEngine::BLUE);
}

void LevelManager::makeUI()
{
  	ObjectManager::getInstance().Add(L"Start Screen", { 0.0f , 0.0f }, { 0.0f, 0.0f }, 0.0f, 1.0f, 1.0f);
	ObjectManager::getInstance().Add(L"Health Bar", { 0.0f , 900.0f }, { 0.0f, 0.0f }, 0.0f, 4.0f);
}

void LevelManager::CreateBackground(int length)
{
	float size = 2048.0f;				// hardcoded. Should be dependent on the width of the picture
	float widthScale = 2.0f;			// hardcoded
	for (int i = 0; i < length; i++) {
		ObjectManager::getInstance().Add(L"Dungeon Background", { -2000.0f + size * i * widthScale, 0.0f }, { 0.0f, 0.0f }, 0.0f, widthScale, 2.0f, 1);
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
	for (int i = 1; i <= 5; i++) {
		ObjectManager::getInstance().Add(L"Weak Zombie", Vector2D(i * 100.0f, 300.0f), {}, 0.0f, 3.5f, 3.5f,1);
		numEnemies += 1;
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

void LevelManager::SetXPos(int Xpos)
{
	this->XPos = Xpos;
}

void LevelManager::SetHP(int hp)
{
	this->heroHealth = hp;
}

void LevelManager::SetMaxHP(int hp)
{
	this->maxHeroHealth = hp;
}
