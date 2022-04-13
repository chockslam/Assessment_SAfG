/*
	* Level Manager .cpp file
	* 19012503
	* Aim: Manages the state of level and keeps track of levels too 
	* as well as provides mechanism of communication between various objects (functions implementation).
	* Notes : Should be rendered and updated the last.
*/



#include "LevelManager.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "ObjectManager.h"
#include <string>



//---------------- TIMERS ------------------------------------------------------//
#define END_TIMER 400.0f				//Level End Timer
#define START_TIMER 100.0f				//Level Star Timer
#define DEATH_COOL_DOWN_PLAYER 500.0f	//Death cooldown
//---------------- TIMERS ------------------------------------------------------//



//---------------- MISC MACROS ------------------------------------------------------//
#define MAIN_THEME_MUSIC_FILE L"assets\\main_sounds\\NoteDefender_Menu.wav"
#define NUMBER_OF_LEVELS 2
#define MAIN_SONG_VOLUME -500
//---------------- MISC MACROS ------------------------------------------------------//

//----------------LEVEL ONE PRESET------------------------------------------------------//
#define LEVEL_ONE 1
#define LEVEL_ONE_BACKGROUND L"Dungeon Background"
#define LEVEL_ONE_FOREGROUND L"Green Fog"
#define LEVEL_ONE_MAX_REACH 2000.0f

#define LEVEL_ONE_POWERUP_NUMS 5

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

#define LEVEL_ONE_TIMER 40.0f;
//----------------LEVEL ONE PRESET------------------------------------------------------//



//----------------LEVEL TWO PRESET------------------------------------------------------//
#define LEVEL_TWO 2
#define LEVEL_TWO_BACKGROUND L"Forrest Background"
#define LEVEL_TWO_FOREGROUND L"Yellow Fog"
#define LEVEL_TWO_MAX_REACH 3000.0f

#define LEVEL_TWO_POWERUP_NUMS 10

#define LEVEL_TWO_WEAK_ZOMBIE_NUMBER 7;
#define LEVEL_TWO_WEAK_CRAWLER_NUMBER 7;
#define LEVEL_TWO_NORMAL_ZOMBIE_NUMBER 7;
#define LEVEL_TWO_NORMAL_CRAWLER_NUMBER 5;
#define LEVEL_TWO_HARD_ZOMBIE_NUMBER 3;
#define LEVEL_TWO_HARD_CRAWLER_NUMBER 2;

#define LEVEL_TWO_MAX_Y 500
#define LEVEL_TWO_MIN_Y -550
#define LEVEL_TWO_MAX_X 12000
#define LEVEL_TWO_MIN_X -2100


#define LEVEL_TWO_TIMER 60.0f;
//----------------LEVEL TWO PRESET------------------------------------------------------//

// constructor default
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
	this->levelTimer = 10.0f;
}

/// <summary>
/// Function which starts level when called.
/// It is public because level 1 needs to be started when level manager is created.
/// </summary>
/// <param name="level"> level to be started </param>
void LevelManager::StartLevel(int level)
{


	this->level = level;

	MySoundEngine::GetInstance()->StopAllSounds();
	MySoundEngine::GetInstance()->Play(this->mainSong, true);

	// Set level one initial parameters
	if (this->level == LEVEL_ONE) {
		this->minY = LEVEL_ONE_MIN_Y;
		this->maxY = LEVEL_ONE_MAX_Y;
		this->minX = LEVEL_ONE_MIN_X;
		this->maxX = LEVEL_ONE_MAX_X;
		this->maxReach = LEVEL_ONE_MAX_REACH;
		this->levelTimer = LEVEL_ONE_TIMER;
	}

	// Set level two initial parameters
	if (this->level == LEVEL_TWO) {
		this->minY = LEVEL_TWO_MIN_Y;
		this->maxY = LEVEL_TWO_MAX_Y;
		this->minX = LEVEL_TWO_MIN_X;
		this->maxX = LEVEL_TWO_MAX_X;
		this->maxReach = LEVEL_TWO_MAX_REACH;
		this->levelTimer = LEVEL_TWO_TIMER;
	}
	// do level-starting actions, only if the level does not exceeds maximum allowed level.
	if (this->level <= NUMBER_OF_LEVELS) {
		
		this->numEnemies = 0;							// reset enemies counter

		this->startGameTimer = START_TIMER;				// Start screen showing time
		this->endGameTimer = 0.0f;						// Mission Complete screen showing time - reset.

		this->CreateBackground(5);						// Map

		// Respawn objects
		RespawnPlayer();								
		RespawnEnemies();
		RespawnPowerUps();


		this->CreateForeground(3);						// Fog

		makeUI();										// Ui


	}
	
	
}

/// <summary>
/// Initialize related functionality.
/// </summary>
void LevelManager::Initialize()
{

	// Stop all sounds before assigning new ones.
	MySoundEngine::GetInstance()->StopAllSounds();

	// Load song and set volume
	this->mainSong = MySoundEngine::GetInstance()->LoadWav(MAIN_THEME_MUSIC_FILE);
	MySoundEngine::GetInstance()->SetVolume(this->mainSong, MAIN_SONG_VOLUME);

	// Just in case set level one settings
	this->startGameTimer = START_TIMER;
	this->endGameTimer = 0.0f;
	this->playerLives = 1;
	this->level = LEVEL_ONE;
	this->minY = LEVEL_ONE_MIN_Y;
	this->maxY = LEVEL_ONE_MAX_Y;
	this->minX = LEVEL_ONE_MIN_X;
	this->maxX = LEVEL_ONE_MAX_X;
	this->maxReach = LEVEL_ONE_MAX_REACH;
	
}


/// <summary>
/// Update LM
/// </summary>
/// <param name="timeFrame"> time between frames </param>
void LevelManager::Updated(float timeFrame)
{
	// show start game screen for several seconds
	if (startGameTimer > 0.0f)
	{
		startGameTimer -= timeFrame;
	}
	// Process successful end of the level, i.e. keep showing end screen and start next level after that.
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
	// if level timer has not run out, keep running default level update, i.e. game is running.
	if (this->levelTimer>0.0f)
	{
		this->levelTimer -= timeFrame;
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
		// if all enemies killed show end screen.
		if (numEnemies == 0) {
			endGameTimer = END_TIMER;
			ObjectManager::getInstance().Add(L"End Screen", { 0.0f , 0.0f }, { 0.0f, 0.0f }, 0.0f, 0.7f, 0.7f);
		}
	}
	// if level timer has expired, start First level.
	else {
		ObjectManager::getInstance().InactivateAll();
		this->level = LEVEL_ONE;
		StartLevel(this->level);
	}
	
	// Process proximity between zombies and a hero. zombies chase a player if they are close enough. 
	// Primitive interaction...
	ObjectManager::getInstance().checkOtherInteraction(L"Zombies", L"Player", this->maxReach);
}

/// <summary>
/// Render text in the screen
/// </summary>
void LevelManager::Render()
{
	std::wstring zNumText = L"KILL        " + std::to_wstring(this->numEnemies) + L"        MORE ZOMBIES";
	MyDrawEngine::GetInstance()->WriteText(50, 40, zNumText.c_str(),
		MyDrawEngine::GREEN);

	std::wstring timeLeftText = L"TIME LEFT:   " + std::to_wstring(this->levelTimer);

	MyDrawEngine::GetInstance()->WriteText(50, 100, timeLeftText.c_str(),
		MyDrawEngine::GREEN);

	// show 'HURRY UP' sign if remaining time is less then 20.0f
	if (this->levelTimer<=20.0f) {
		MyDrawEngine::GetInstance()->WriteText(50, 120, L"HURRY UP!!!",
			MyDrawEngine::RED);
	}
	//MyDrawEngine::GetInstance()->WriteInt(150, 50, playerLives,
	//	MyDrawEngine::GREEN);
	//MyDrawEngine::GetInstance()->WriteInt(250, 50, XPos,
	//	MyDrawEngine::BLUE);
}

/// <summary>
/// Handle UI elements
/// </summary>
void LevelManager::makeUI()
{
	// Handle Start sceen and Health bar
  	ObjectManager::getInstance().Add(L"Start Screen", { 0.0f , 0.0f }, { 0.0f, 0.0f }, 0.0f, 1.0f, 1.0f);
	ObjectManager::getInstance().Add(L"Health Bar", { 0.0f , 900.0f }, { 0.0f, 0.0f }, 0.0f, 4.0f);
}

/// <summary>
/// Draw a background for the level.
/// It is looks funky on edges of each image
/// </summary>
/// <param name="length"> number of images to draw </param>
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
/// <summary>
/// Create a foreground Fog effects.
/// It is looks funky on edges of each image
/// </summary>
/// <param name="length"></param>
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

/// <summary>
/// Spawn a bunch of zombies.
/// </summary>
void LevelManager::RespawnEnemies()
{
	int numWeakZ = 0;
	int numWeakC = 0;
	int numNormalZ = 0;
	int numNormalC = 0;
	int numHardZ = 0;
	int numHardC = 0;

	// Each level has different numbers each zombie types.
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
	// Add number of zombies and randomly place them within boundaries of the map.
	for (int i = 1; i <= numWeakZ; i++) {
		ObjectManager::getInstance().Add(L"Weak Zombie",	Vector2D(1000 + rand() % (this->maxX - 1000), rand() % (this->maxY + abs(this->minY)) + this->minY), {}, 0.0f, 3.5f, 3.5f, rand() % 2 + 1);
		numEnemies += 1;
	}
	for (int i = 1; i <= numWeakC; i++) {
		ObjectManager::getInstance().Add(L"Weak Crawler",	Vector2D(1000 + rand() % (this->maxX - 1000), rand() % (this->maxY + abs(this->minY)) + this->minY), {}, 0.0f, 3.5f, 3.5f, rand()%2+1);
		numEnemies += 1;
	}
	for (int i = 1; i <= numNormalZ; i++) {
		ObjectManager::getInstance().Add(L"Normal Zombie",	Vector2D(1000 + rand() % (this->maxX - 1000), rand() % (this->maxY + abs(this->minY)) + this->minY), {}, 0.0f, 3.5f, 3.5f, rand() % 2 + 1);
		numEnemies += 1;
	}
	for (int i = 1; i <= numNormalC; i++) {
		ObjectManager::getInstance().Add(L"Normal Crawler",	Vector2D(1000 + rand() % (this->maxX - 1000), rand() % (this->maxY + abs(this->minY)) + this->minY), {}, 0.0f, 3.5f, 3.5f, rand() % 2 + 1);
		numEnemies += 1;
	}
	for (int i = 1; i <= numHardZ; i++) {
		ObjectManager::getInstance().Add(L"Hard Zombie",	Vector2D(1000 + rand() % (this->maxX - 1000), rand() % (this->maxY + abs(this->minY)) + this->minY), {}, 0.0f, 3.5f, 3.5f, rand() % 2 + 1);
		numEnemies += 1;
	}
	for (int i = 1; i <= numHardC; i++) {
		ObjectManager::getInstance().Add(L"Hard Crawler",	Vector2D(1000 + rand() % (this->maxX - 1000), rand() % (this->maxY + abs(this->minY)) + this->minY), {}, 0.0f, 3.5f, 3.5f, rand() % 2 + 1);
		numEnemies += 1;
	}
}
/// <summary>
/// Spawn a player.
/// </summary>
void LevelManager::RespawnPlayer()
{
	ObjectManager::getInstance().Add(	L"Player",
										{ -3000.0f, 0.0f },
										{ 0.0f, 0.0f },
										4.5f,
										4.5f,
										0.0f,
										1
									);
}

/// <summary>
/// Respawn power ups.
/// </summary>
void LevelManager::RespawnPowerUps()
{

	// Each level has different numbers of power-ups.
	int numPowerUps = 1;
	if (this->level == 1) {
		numPowerUps = LEVEL_ONE_POWERUP_NUMS;
	}
	else if (this->level == 2) {
		numPowerUps = LEVEL_TWO_POWERUP_NUMS;
	}

	for (int i = 1; i <= numPowerUps; i++) {
		ObjectManager::getInstance().Add(	L"Power Up", 
											Vector2D(300 + rand() % (this->maxX - 1000), rand() % (this->maxY + abs(this->minY)) + this->minY),
											{},
											0.0f,
											3.5f,
											3.5f,
											this->level
										);  // different appearance of power ups for each level. it is implied that level does not exceed 7.
	}
}


void LevelManager::EnemyDead()
{
	numEnemies--;
}

void LevelManager::PlayerDead()
{
	playerLives--;
}

/// <summary>
/// was used to set level boundaries.
/// </summary>
/// <param name="Ypos"></param>
void LevelManager::SetYPos(int Ypos)
{
	this->YPos = Ypos;
}


/// <summary>
/// was used to set level boundaries.
/// </summary>
/// <param name="Ypos"></param>
void LevelManager::SetXPos(int Xpos)
{
	this->XPos = Xpos;
}


/// <summary>
/// Used to communicate current health between Hero and LevelManager.
/// </summary>
void LevelManager::SetHP(int hp)
{
	this->heroHealth = hp;
}

/// <summary>
/// Used to communicate max health between Hero and LevelManager.
/// </summary>
void LevelManager::SetMaxHP(int hp)
{
	this->maxHeroHealth = hp;
}
