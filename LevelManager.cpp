#include "LevelManager.h"
#include "mydrawengine.h"
#include "ObjectManager.h"
#include <string>

#define END_TIMER 400.0f
#define START_TIMER 100.0f
#define DEATH_COOL_DOWN_PLAYER 500.0f


#define NUMBER_OF_LEVELS 2

#define LEVEL_ONE 1
#define LEVEL_ONE_BACKGROUND L"Dungeon Background"
#define LEVEL_ONE_FOREGROUND L"Green Fog"
#define LEVEL_ONE_MAX_REACH 2000.0f

#define LEVEL_ONE_WEAK_ZOMBIE_NUMBER 10;
#define LEVEL_ONE_WEAK_CRAWLER_NUMBER 5;
#define LEVEL_ONE_NORMAL_ZOMBIE_NUMBER 1;
#define LEVEL_ONE_NORMAL_CRAWLER_NUMBER 1;
#define LEVEL_ONE_HARD_ZOMBIE_NUMBER 1;
#define LEVEL_ONE_HARD_CRAWLER_NUMBER 1;

#define LEVEL_ONE_MAX_Y 492
#define LEVEL_ONE_MIN_Y -877
#define LEVEL_ONE_MAX_X 12000
#define LEVEL_ONE_MIN_X -2100



#define LEVEL_TWO 2
#define LEVEL_TWO_BACKGROUND L"Forrest Background"
#define LEVEL_TWO_FOREGROUND L"Yellow Fog"
#define LEVEL_TWO_MAX_REACH 3000.0f

#define LEVEL_TWO_WEAK_ZOMBIE_NUMBER 15;
#define LEVEL_TWO_WEAK_CRAWLER_NUMBER 9;
#define LEVEL_TWO_NORMAL_ZOMBIE_NUMBER 7;
#define LEVEL_TWO_NORMAL_CRAWLER_NUMBER 5;
#define LEVEL_TWO_HARD_ZOMBIE_NUMBER 3;
#define LEVEL_TWO_HARD_CRAWLER_NUMBER 2;

#define LEVEL_TWO_MAX_Y 500
#define LEVEL_TWO_MIN_Y -550
#define LEVEL_TWO_MAX_X 12000
#define LEVEL_TWO_MIN_X -2100


LevelManager::LevelManager()
	:
	GameObject::GameObject(Vector2D(0, 0), 0, 0, 0, false, {}),
	numEnemies(0),
	playerLives(1),
	minY(-100000000),
	maxY(100000000),
	level(1),
	playerDeathCoolDownTimer(DEATH_COOL_DOWN_PLAYER)
{
	type = ObjectType::LEVEL_MANAGER;
}

void LevelManager::StartLevel(int level)
{
	
	this->level = level;

	if (this->level == LEVEL_ONE) {
		this->minY = LEVEL_ONE_MIN_Y;
		this->maxY = LEVEL_ONE_MAX_Y;
		this->minX = LEVEL_ONE_MIN_X;
		this->maxX = LEVEL_ONE_MAX_X;
		this->maxReach = LEVEL_ONE_MAX_REACH;
	}
	
	if (this->level == LEVEL_TWO) {
		this->minY = LEVEL_TWO_MIN_Y;
		this->maxY = LEVEL_TWO_MAX_Y;
		this->minX = LEVEL_TWO_MIN_X;
		this->maxX = LEVEL_TWO_MAX_X;
		this->maxReach = LEVEL_TWO_MAX_REACH;
	}
	if (this->level <= NUMBER_OF_LEVELS) {
		this->startGameTimer = START_TIMER;
		this->endGameTimer = 0.0f;

		this->CreateBackground(5);

		RespawnPlayer();
		RespawnEnemies();

		this->CreateForeground(3);


		makeUI();
	}
	
	
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
	this->maxReach = LEVEL_ONE_MAX_REACH;
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
			this->level = (this->level < NUMBER_OF_LEVELS) ? this->level + 1 : LEVEL_ONE;
			StartLevel(this->level);
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
	

	ObjectManager::getInstance().checkOtherInteraction(L"Zombies", L"Player", this->maxReach);
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
	std::wstring backG = L"";
	if(this->level == LEVEL_ONE) {
		backG = LEVEL_ONE_BACKGROUND;
	}
	else if (this->level == LEVEL_TWO) {
		backG = LEVEL_TWO_BACKGROUND;
	}
	float size = 2048.0f;				// hardcoded. Should be dependent on the width of the picture
	float widthScale = 3.0f;			// hardcoded
	for (int i = 0; i < length; i++) {
		ObjectManager::getInstance().Add(backG, { -2000.0f + size * i * widthScale, 0.0f }, { 0.0f, 0.0f }, 0.0f, widthScale, 2.0f, 1);
	}
}

void LevelManager::CreateForeground(int length)
{
	std::wstring foreG = L"";
	if (this->level == LEVEL_ONE) {
		foreG = LEVEL_ONE_FOREGROUND;
	}
	else if (this->level == LEVEL_TWO) {
		foreG = LEVEL_TWO_FOREGROUND;
	}
	float size = 2048.0f;				// hardcoded. Should be dependent on the width of the picture
	float widthScale = 3.0f;			// hardcoded
	for (int i = 0; i < length; i++) {
		ObjectManager::getInstance().Add(foreG, { -850.0f + size * i *widthScale, 0.0f }, { 0.0f, 0.0f }, 0.0f, widthScale, 9.0f, 1);
	}
}

void LevelManager::RespawnEnemies()
{
	int numWeakZ = 0;
	int numWeakC = 0;
	int numNormalZ = 0;
	int numNormalC = 0;
	int numHardZ = 0;
	int numHardC = 0;

	if (this->level == 1) {
		numWeakZ = LEVEL_ONE_WEAK_ZOMBIE_NUMBER;
		numWeakC = LEVEL_ONE_WEAK_CRAWLER_NUMBER;
		numNormalZ = LEVEL_ONE_NORMAL_ZOMBIE_NUMBER;
		numNormalC = LEVEL_ONE_NORMAL_CRAWLER_NUMBER;
		numHardZ = LEVEL_ONE_HARD_ZOMBIE_NUMBER;
		numHardC = LEVEL_ONE_HARD_CRAWLER_NUMBER;
	}
	if (this->level == 2) {
		numWeakZ = LEVEL_TWO_WEAK_ZOMBIE_NUMBER;
		numWeakC = LEVEL_TWO_WEAK_CRAWLER_NUMBER;
		numNormalZ = LEVEL_TWO_NORMAL_ZOMBIE_NUMBER;
		numNormalC = LEVEL_TWO_NORMAL_CRAWLER_NUMBER;
		numHardZ = LEVEL_TWO_HARD_ZOMBIE_NUMBER;
		numHardC = LEVEL_TWO_HARD_CRAWLER_NUMBER;
	}
	for (int i = 1; i <= numWeakZ; i++) {
		ObjectManager::getInstance().Add(L"Weak Zombie", Vector2D(rand() % this->maxX, rand() % (this->maxY + abs(this->minY)) + this->minY), {}, 0.0f, 3.5f, 3.5f, rand() % 2 + 1);
		numEnemies += 1;
	}
	for (int i = 1; i <= numWeakC; i++) {
		ObjectManager::getInstance().Add(L"Weak Crawler", Vector2D(rand() % this->maxX, rand() % (this->maxY + abs(this->minY)) + this->minY), {}, 0.0f, 3.5f, 3.5f, rand()%2+1);
		numEnemies += 1;
	}
	for (int i = 1; i <= numWeakZ; i++) {
		ObjectManager::getInstance().Add(L"Normal Zombie", Vector2D(rand() % this->maxX, rand() % (this->maxY + abs(this->minY)) + this->minY), {}, 0.0f, 3.5f, 3.5f, rand() % 2 + 1);
		numEnemies += 1;
	}
	for (int i = 1; i <= numNormalC; i++) {
		ObjectManager::getInstance().Add(L"Normal Crawler", Vector2D(rand() % this->maxX, rand() % (this->maxY + abs(this->minY)) + this->minY), {}, 0.0f, 3.5f, 3.5f, rand() % 2 + 1);
		numEnemies += 1;
	}
	for (int i = 1; i <= numHardZ; i++) {
		ObjectManager::getInstance().Add(L"Hard Zombie", Vector2D(rand() % this->maxX, rand() % (this->maxY + abs(this->minY)) + this->minY), {}, 0.0f, 3.5f, 3.5f, rand() % 2 + 1);
		numEnemies += 1;
	}
	for (int i = 1; i <= numHardC; i++) {
		ObjectManager::getInstance().Add(L"Hard Crawler", Vector2D(rand() % this->maxX, rand() % (this->maxY + abs(this->minY)) + this->minY), {}, 0.0f, 3.5f, 3.5f, rand() % 2 + 1);
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
