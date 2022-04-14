/*
	* Object Manager .h file
	* 19012503
	* Aim of the class:		Game Engine related class, which manages objects in various ways: collisions, update, rendering, deletion of objects is done here.
	*						The class also has an extension functionality related to Object Factory.
	*						(functions implementation)
*/

#include "ObjectManager.h"
#include "mydrawengine.h"
#include "Zombie.h"
#include "Hero.h"
#include "Sprite.h"
#include "LevelManager.h"
#include "HealthBar.h"
#include "PowerUp.h"
#include "DeadScreen.h"
#include "StartScreen.h"
#include "EndScreen.h"
#include "Bullet.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include "AnimMasks.h"

#include <typeinfo>

/// <summary>
/// Object factory related function.
/// Decouples creation of objects from other part of the game engine/ game logic.
/// </summary>
/// <param name="name"> name of the object to be created</param>
/// <param name="pos">position</param>
/// <param name="vel">initial velocity</param>
/// <param name="rot">rotation</param>
/// <param name="sizeX">Scale accros x axis</param>
/// <param name="sizeY">Scale accros y axis</param>
/// <param name="appearance"> image/appearence of the object - not applied to all </param>
void ObjectManager::Add(std::wstring name, Vector2D pos, Vector2D vel, float rot, float sizeX, float sizeY, int appearance)
{

	// will be added to the list of all objects
	std::shared_ptr<GameObject> go = nullptr;
	// will be added to the list of collidable objects
	std::shared_ptr<CollidableObject> cgo = nullptr;

	// map on animations...
	std::unordered_map<std::wstring, std::list<std::wstring>> anims;

	//-------------------------------VARIOUS OBJECTS---------------------------------------------------//
	//-------------------------------VARIOUS OBJECTS---------------------------------------------------//
	//-------------------------------VARIOUS OBJECTS---------------------------------------------------//
	if (name == L"Weak Zombie") 
	{

		// IDLE ANIMATION
		anims[IDLE] = std::list<std::wstring>{ 
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_5.png",
		};

		// RUN ANIMATION
		anims[RUN] = std::list<std::wstring>{ 
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_5.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_6.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_7.png"
		};

		// FALL ANIMATION
		anims[FALL] = std::list<std::wstring>{ 
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png"
		};

		// ATTACK ANIMATION
		anims[ATTACK] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_5.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_6.png"
		};

		// DEATH ANIMATION
		anims[DEATH] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_5.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_6.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png"
		};
		auto z = std::make_shared<Zombie>(pos, vel, rot, sizeX, sizeY, false, anims);
		// weak zombie's level ranges from 0-5.
		z->setLevel(rand() % 6);
		cgo = z;
		// push the pointer to the list of collidable objects
		pObjectCollidable.push_back(cgo);
		// interpret it as a GameObject to push it to the list later.
		go = cgo;
	}
	if (name == L"Normal Zombie") 
	{
		anims[IDLE] = std::list<std::wstring>{ 
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_5.png",
		};
		anims[RUN] = std::list<std::wstring>{ 
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_5.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_6.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_7.png"
		};
		anims[FALL] = std::list<std::wstring>{ 
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png"
		};
		anims[ATTACK] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_5.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_6.png"
		};

		anims[DEATH] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_5.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_6.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png"
		};
		auto z = std::make_shared<Zombie>(pos, vel, rot, sizeX, sizeY, false, anims);
		z->setLevel(rand() % 5 + 6);
		cgo = z;
		pObjectCollidable.push_back(cgo);
		go = cgo;
	}

	if (name == L"Weak Crawler")
	{
		anims[IDLE] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_5.png",
		};
		anims[RUN] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_5.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_6.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_7.png"
		};
		anims[FALL] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png"
		};
		anims[ATTACK] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_5.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_6.png"
		};
		anims[DEATH] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_5.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_6.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png"
		};
		auto z = std::make_shared<Zombie>(pos, vel, rot, sizeX, sizeY, false, anims);
		z->setLevel(rand() % 6);
		cgo = z;
		pObjectCollidable.push_back(cgo);
		go = cgo;
	}
	if (name == L"Normal Crawler")
	{
		anims[IDLE] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_5.png",
		};
		anims[RUN] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_5.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_6.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_7.png"
		};
		anims[FALL] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png"
		};
		anims[ATTACK] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_5.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_6.png"
		};
		anims[DEATH] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_5.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_6.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png"
		};
		auto z = std::make_shared<Zombie>(pos, vel, rot, sizeX, sizeY, false, anims);
		z->setLevel(rand() % 5 + 6);
		cgo = z;
		pObjectCollidable.push_back(cgo);
		go = cgo;
	}
	if (name == L"Hard Zombie")
	{
		anims[IDLE] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_5.png",
		};
		anims[RUN] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_5.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_6.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_7.png"
		};
		anims[FALL] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png"
		};
		anims[ATTACK] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_5.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_6.png"
		};
		anims[DEATH] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_5.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_6.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png"
		};
		auto z = std::make_shared<Zombie>(pos, vel, rot, sizeX, sizeY, false, anims);
		z->setLevel(rand() % 11 + 10);
		cgo = z;
		pObjectCollidable.push_back(cgo);
		go = cgo;
	}
	if (name == L"Hard Crawler")
	{
		anims[IDLE] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_5.png",
		};
		anims[RUN] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_5.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_6.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_7.png"
		};
		anims[FALL] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png"
		};
		anims[ATTACK] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_5.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_6.png"
		};
		anims[DEATH] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_5.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_6.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png"
		};
		auto z = std::make_shared<Zombie>(pos, vel, rot, sizeX, sizeY, false, anims);
		z->setLevel(rand() % 11 + 10);
		cgo = z;
		pObjectCollidable.push_back(cgo);
		go = cgo;
	}

	if (name == L"Player") 
	{
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\player\\idle_1.png",
				L"assets\\player\\idle_2.png",
				L"assets\\player\\idle_5.png",
				L"assets\\player\\idle_6.png",
				L"assets\\player\\idle_7.png",
		};

		anims[RUN] = std::list<std::wstring>{
				L"assets\\player\\run_1.png",
				L"assets\\player\\run_2.png",
				L"assets\\player\\run_3.png",
				L"assets\\player\\run_4.png",
				L"assets\\player\\run_5.png",
				L"assets\\player\\run_6.png",
				L"assets\\player\\run_7.png",
				L"assets\\player\\run_8.png",
		};
		anims[FALL] = std::list<std::wstring>{
				L"assets\\player\\fall_1.png",
				L"assets\\player\\fall_1.png",
				L"assets\\player\\fall_1.png",
				L"assets\\player\\fall_1.png",
				L"assets\\player\\fall_1.png",
				L"assets\\player\\fall_2.png",
				L"assets\\player\\fall_2.png",
				L"assets\\player\\fall_3.png",
				L"assets\\player\\fall_3_5.png",
				L"assets\\player\\idle_1.png",
		};
		anims[ATTACK] = std::list<std::wstring>{
				L"assets\\player\\attack_1.png",
				L"assets\\player\\attack_2.png",
				L"assets\\player\\attack_3.png",
				L"assets\\player\\attack_4.png"
		};
		anims[DEATH] = std::list<std::wstring>{
				L"assets\\player\\fall_2.png",
				L"assets\\player\\fall_2.png",
				L"assets\\player\\fall_2.png",
				L"assets\\player\\fall_3.png",
				L"assets\\player\\fall_3.png",
				L"assets\\player\\fall_3.png",
		};
		cgo = std::make_shared<Hero>(pos, vel, rot, sizeX, sizeY, false, anims);
		
		pObjectCollidable.push_back(cgo);

		go = cgo;
		
	}
	if (name == L"Bullet") 
	{
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\fire\\fire_1.png",
				L"assets\\fire\\fire_2.png",
				L"assets\\fire\\fire_3.png",
				L"assets\\fire\\fire_4.png",
				L"assets\\fire\\fire_5.png",
				L"assets\\fire\\fire_6.png",
				L"assets\\fire\\fire_7.png",
				L"assets\\fire\\fire_8.png",
				L"assets\\fire\\fire_9.png",
				L"assets\\fire\\fire_10.png",
				L"assets\\fire\\fire_11.png",
				L"assets\\fire\\fire_12.png",
				L"assets\\fire\\fire_13.png",
				L"assets\\fire\\fire_14.png",
				L"assets\\fire\\fire_15.png"
		};
		cgo = std::make_shared<Bullet>(pos, vel, rot, sizeX, sizeY, false, anims);
		
		pObjectCollidable.push_back(cgo);

		go = cgo;

	}
	if (name == L"Strong Bullet") 
	{
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\fire\\fire_1.png",
				L"assets\\fire\\fire_2.png",
				L"assets\\fire\\fire_3.png",
				L"assets\\fire\\fire_4.png",
				L"assets\\fire\\fire_5.png",
				L"assets\\fire\\fire_6.png",
				L"assets\\fire\\fire_7.png",
				L"assets\\fire\\fire_8.png",
				L"assets\\fire\\fire_9.png",
				L"assets\\fire\\fire_10.png",
				L"assets\\fire\\fire_8.png",
				L"assets\\fire\\fire_9.png",
				L"assets\\fire\\fire_10.png",
				L"assets\\fire\\fire_8.png",
				L"assets\\fire\\fire_9.png",
				L"assets\\fire\\fire_10.png",
				L"assets\\fire\\fire_8.png",
				L"assets\\fire\\fire_9.png",
				L"assets\\fire\\fire_10.png",
				L"assets\\fire\\fire_11.png",
				L"assets\\fire\\fire_12.png",
				L"assets\\fire\\fire_13.png",
				L"assets\\fire\\fire_14.png",
				L"assets\\fire\\fire_15.png"
		};
		auto bullet = std::make_shared<Bullet>(pos, vel, rot, sizeX * 1.5f, sizeY * 1.5f, false, anims);
		bullet->MakeStrong();
		cgo = std::move(bullet);
		pObjectCollidable.push_back(cgo);
		go = cgo;

	}


	if (name == L"Power Up")
	{
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\powerup\\p" + std::to_wstring(appearance) + L"\\pu1.png",
				L"assets\\powerup\\p" + std::to_wstring(appearance) + L"\\pu2.png",
				L"assets\\powerup\\p" + std::to_wstring(appearance) + L"\\pu3.png",
				L"assets\\powerup\\p" + std::to_wstring(appearance) + L"\\pu4.png"
		};
		cgo = std::make_shared<PowerUp>(pos, vel, rot, sizeX, sizeY, false, anims);

		pObjectCollidable.push_back(cgo);

		go = cgo;


	}
	if (name == L"Green Fog") {
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\fog\\g_fog_1.png",
				L"assets\\fog\\g_fog_2.png",
				L"assets\\fog\\g_fog_3.png",
		};
		auto sp  = std::make_shared<Sprite>(pos, rot, sizeX, sizeY, false, anims);
		sp->repeatOn(true, 0.25f);
		go = sp;
	}
	if (name == L"Blue Fog") {
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\fog\\b_fog_1.png",
				L"assets\\fog\\b_fog_2.png",
				L"assets\\fog\\b_fog_3.png",
		};
		auto sp  = std::make_shared<Sprite>(pos, rot, sizeX, sizeY, false, anims);
		sp->repeatOn(true, 0.25f);
		go = sp;
	}
	if (name == L"Yellow Fog") {
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\fog\\y_fog_1.png",
				L"assets\\fog\\y_fog_2.png",
				L"assets\\fog\\y_fog_3.png",
		};
		auto sp  = std::make_shared<Sprite>(pos, rot, sizeX, sizeY, false, anims);
		sp->repeatOn(true , 0.25f);
		go = sp;
	}
	if (name == L"Dungeon Background") {
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\backgrounds\\battleback8.png",
		};
		auto sp  = std::make_shared<Sprite>(pos, rot, sizeX, sizeY, false, anims);
		go = sp;
	}
	if (name == L"Forrest Background") {
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\backgrounds\\battleback7.png",
		};
		auto sp  = std::make_shared<Sprite>(pos, rot, sizeX, sizeY, false, anims);
		go = sp;
	}

	if (name == L"Level Manager") {
		this->lm = std::make_shared<LevelManager>();
		this->lm->Initialize();
		this->lm->Activate();
		this->lm->StartLevel();
	}

	if (name == L"Health Bar") {
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\ui\\blood_bar.png",
		};
		auto sp = std::make_shared<HealthBar>(pos, rot, sizeX, sizeY, false, anims);
		go = sp;
	}

	if (name == L"Dead Screen") {
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\ui\\dead_skull.png",
		};
		auto sp = std::make_shared<DeadScreen>(pos, rot, sizeX, sizeY, false, anims);
		go = sp;
	}
	if (name == L"Start Screen") {
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\ui\\zombies_screen.png",
		};
		auto sp = std::make_shared<StartScreen>(pos, rot, sizeX, sizeY, false, anims);
		go = sp;
	}
	if (name == L"End Screen") {
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\ui\\level_complete-mini.png",
		};
		auto sp = std::make_shared<EndScreen>(pos, rot, sizeX, sizeY, false, anims);
		go = sp;
	}

	//-------------------------------VARIOUS OBJECTS---------------------------------------------------//
	//-------------------------------VARIOUS OBJECTS---------------------------------------------------//
	//-------------------------------VARIOUS OBJECTS---------------------------------------------------//
	
	
	if (go) {
		// Initialize, activate and push GameObject to the object list.
		go->Initialize();
		go->Activate();
		pObjectList.push_back(std::move(go));
	}
	

}

/// <summary>
/// Update All GameObjects.
/// </summary>
/// <param name="frameTime">time between frames</param>
void ObjectManager::UpdateAll(float frameTime)
{
	for (auto& obj : this->pObjectList) {
		obj->Updated(frameTime);
	}

	// Level Manager should be updated the last.
	lm->Updated(frameTime);
	
	// Check Collision after update every frame.
	CheckCollisions();
}

/// <summary>
/// Render all GameObjects
/// </summary>
void ObjectManager::RenderAll()
{


	for (auto& obj : this->pObjectList) {
		obj->Render();
	}

	// Level Manager should be rendered the last.
	lm->Render();

}

/// <summary>
/// Delete objects from all the lists.
/// </summary>
void ObjectManager::DeleteAll()
{
	
	pObjectList.clear();
	pObjectCollidable.clear();
}

/// <summary>
/// Delete all inactive objects from all the lists.
/// </summary>
void ObjectManager::DeleteInactive()
{
	for (auto& obj : pObjectList) 
	{
		if (!obj->IsActive())
  			obj.reset();
	}
	
	for (auto& obj : pObjectCollidable) 
	{
		if (!obj->IsActive())
  			obj.reset();
	}

	
	pObjectCollidable.remove(NULL);
	pObjectList.remove(NULL);
}

/// <summary>
/// Inactivate all objects in the list.
/// </summary>
void ObjectManager::InactivateAll()
{
	for(auto& pObj: pObjectList){
			pObj->Deactivate();
	}
}

/// <summary>
/// Collision checking function.
/// </summary>
void ObjectManager::CheckCollisions() 
{
	std::list<std::shared_ptr<CollidableObject>>::iterator it1;
	std::list<std::shared_ptr<CollidableObject>>::iterator it2;
	for (it1 = pObjectCollidable.begin(); it1 != pObjectCollidable.end(); it1++)
	{
		if ((*it1) && 
			(*it1)->IsActive() &&
			(*it1)->DoesShapeExist()
			) 
		{
			for (it2 = std::next(it1); it2 != pObjectCollidable.end(); it2++)
			{
				if ((*it2) &&
					(*it2)->IsActive() &&
					(*it2)->DoesShapeExist() &&
					(*it1)->GetShape().Intersects((*it2)->GetShape())) 
				{
					(*it1)->ProcessCollision(*it2);
					(*it2)->ProcessCollision(*it1);
				}
			}
		}
	}

}

/// <summary>
/// Functions that checks other interaction between objects rather than just collision.
/// It is used specifically for Zombies and A Hero in the context of the game.
/// Similar to collision cheking.
/// </summary>
/// <param name="objType1">first type of the object to check interaction with</param>
/// <param name="objType2">second type of the object to check interaction with</param>
/// <param name="threshold"> minimum distance to check interaction with. </param>
void ObjectManager::checkOtherInteraction(std::wstring objType1, std::wstring objType2, float threshold)
{
	if (objType1 == L"Zombies" && objType2 == L"Player") {
		// list of all zombies
		auto list = QueryObjectList<Zombie>();
		// A hero.
		auto p = QueryObject<Hero>();
		for (auto obj : list) {
			if (p && obj &&
				p->IsActive() && obj->IsActive()) {
				Vector2D disp = obj->getPos() - p->getPos();
				float magn = disp.magnitude();
				if (magn <= threshold) {
					obj->ProcessProximity(p,magn, threshold);
				}
			}
			
		}
	}
}

ObjectManager::~ObjectManager()
{
	if (!pObjectList.empty()) 
	{
		pObjectList.clear();
	}
}


