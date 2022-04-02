#include "ObjectManager.h"
#include "mydrawengine.h"
#include "Zombie.h"
#include "Hero.h"
#include "Sprite.h"
#include "LevelManager.h"
#include "HealthBar.h"
#include "DeadScreen.h"
#include "StartScreen.h"
#include "EndScreen.h"
#include "Bullet.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include "AnimMasks.h"

#include <typeinfo>


void ObjectManager::Add(std::wstring name, Vector2D pos, Vector2D vel, float rot, float sizeX, float sizeY, int appearance)
{
	std::shared_ptr<GameObject> go = nullptr;
	std::shared_ptr<CollidableObject> cgo = nullptr;

	std::unordered_map<std::wstring, std::list<std::wstring>> anims;

	if (name == L"Weak Zombie") 
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
		z->setLevel(rand() % 6);
		cgo = z;
		pObjectCollidable.push_back(cgo);
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
	
	if (name == L"Explosion") {
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\explosion1.bmp",
				L"assets\\explosion2.bmp",
				L"assets\\explosion3.bmp",
				L"assets\\explosion4.bmp",
				L"assets\\explosion5.bmp",
				L"assets\\explosion6.bmp",
				L"assets\\explosion7.bmp",
				L"assets\\explosion8.bmp"
		};
		go = std::make_shared<Sprite>(pos, rot, sizeX, sizeY, false, anims);
		
	}
	if (name == L"Puff") {
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\puff1.bmp",
				L"assets\\puff2.bmp",
				L"assets\\puff3.bmp",
				L"assets\\puff4.bmp",
				L"assets\\puff5.bmp",
				L"assets\\puff6.bmp",
				L"assets\\puff7.bmp",
				L"assets\\puff8.bmp"
		};
		go = std::make_shared<Sprite>(pos, rot, sizeX, sizeY, false, anims);
		
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
				L"assets\\ui\\level_complete.png",
		};
		auto sp = std::make_shared<EndScreen>(pos, rot, sizeX, sizeY, false, anims);
		go = sp;
	}
	
	if (go) {
		go->Initialize();
		go->Activate();
		pObjectList.push_back(std::move(go));
	}
	

}

void ObjectManager::AddObject(std::shared_ptr<GameObject> object)
{
	this->pObjectList.push_back(std::move(object));
}

void ObjectManager::UpdateAll(float frameTime)
{
	//auto p = QueryObject<Spaceship>();
	//if (p) {
	//	if()
	//}
	for (auto& obj : this->pObjectList) {
		obj->Updated(frameTime);
	}

	// should be updated the last.
	lm->Updated(frameTime);
	
	CheckCollisions();
}

void ObjectManager::RenderAll()
{


	for (auto& obj : this->pObjectList) {
		obj->Render();
	}

	// should be rendered the last.
	lm->Render();

}

void ObjectManager::DeleteAll()
{
	pObjectList.clear();
	pObjectCollidable.clear();
}

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

void ObjectManager::InactivateAll()
{
	for(auto pObj: pObjectList){
		if(pObj->GetType() != ObjectType::LEVEL_MANAGER)
			pObj->Deactivate();
	}
}

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

void ObjectManager::checkOtherInteraction(std::wstring objType1, std::wstring objType2, float threshold)
{
	if (objType1 == L"Zombies" && objType2 == L"Player") {
		auto list = QueryObjectList<Zombie>();
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


