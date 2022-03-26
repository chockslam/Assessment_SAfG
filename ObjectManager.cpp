#include "ObjectManager.h"
#include "mydrawengine.h"
#include "Zombie.h"
#include "Spaceship.h"
#include "Sprite.h"
#include "LevelManager.h"
#include "Bullet.h"
#include <iostream>
#include <string>
#include <unordered_map>



void ObjectManager::Add(std::wstring name, Vector2D pos, Vector2D vel, float rot, float sizeX, float sizeY, int appearance)
{
	std::shared_ptr<GameObject> go;
	std::shared_ptr<CollidableObject> cgo;

	std::unordered_map<std::wstring, std::list<std::wstring>> anims;

	if (name == L"Weak Zombie") 
	{


		anims[L"IDLE"] = std::list<std::wstring>{ 
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_5.png",
		};
		anims[L"RUN"] = std::list<std::wstring>{ 
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_5.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_6.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_7.png"
		};
		anims[L"FALL"] = std::list<std::wstring>{ 
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png"
		};

		anims[L"DEATH"] = std::list<std::wstring>{
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
		z->setLevel(rand() % 5 + 1);
		cgo = z;
		pObjectCollidable.push_back(cgo);
		go = cgo;
	}
	if (name == L"Normal Zombie") 
	{
		anims[L"IDLE"] = std::list<std::wstring>{ 
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_5.png",
		};
		anims[L"RUN"] = std::list<std::wstring>{ 
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_5.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_6.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_7.png"
		};
		anims[L"FALL"] = std::list<std::wstring>{ 
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png"
		};

		anims[L"DEATH"] = std::list<std::wstring>{
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
		z->setLevel(rand() % 5 + 5);
		cgo = z;
		pObjectCollidable.push_back(cgo);
		go = cgo;
	}

	if (name == L"Weak Crawler")
	{
		anims[L"IDLE"] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_5.png",
		};
		anims[L"RUN"] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_5.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_6.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_7.png"
		};
		anims[L"FALL"] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png"
		};
		anims[L"DEATH"] = std::list<std::wstring>{
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
		z->setLevel(rand() % 5 + 1);
		cgo = z;
		pObjectCollidable.push_back(cgo);
		go = cgo;
	}
	if (name == L"Normal Crawler")
	{
		anims[L"IDLE"] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_5.png",
		};
		anims[L"RUN"] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_5.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_6.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_7.png"
		};
		anims[L"FALL"] = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png"
		};
		anims[L"DEATH"] = std::list<std::wstring>{
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
		z->setLevel(rand() % 5 + 5);
		cgo = z;
		pObjectCollidable.push_back(cgo);
		go = cgo;
	}
	if (name == L"Player") 
	{
		anims[L"IDLE"] = std::list<std::wstring>{
				L"assets\\player\\idle_1.png",
				L"assets\\player\\idle_2.png",
				L"assets\\player\\idle_5.png",
				L"assets\\player\\idle_6.png",
				L"assets\\player\\idle_7.png",
		};

		anims[L"RUN"] = std::list<std::wstring>{
				L"assets\\player\\run_1.png",
				L"assets\\player\\run_2.png",
				L"assets\\player\\run_3.png",
				L"assets\\player\\run_4.png",
				L"assets\\player\\run_5.png",
				L"assets\\player\\run_6.png",
				L"assets\\player\\run_7.png",
				L"assets\\player\\run_8.png",
		};
		anims[L"FALL"] = std::list<std::wstring>{
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
		anims[L"DEATH"] = std::list<std::wstring>{
				L"assets\\player\\fall_2.png",
				L"assets\\player\\fall_2.png",
				L"assets\\player\\fall_2.png",
				L"assets\\player\\fall_3.png",
				L"assets\\player\\fall_3.png",
				L"assets\\player\\fall_3.png",
		};
		cgo = std::make_shared<Spaceship>(pos, vel, rot, sizeX, sizeY, false, anims);
		
		pObjectCollidable.push_back(cgo);

		go = cgo;
		
	}
	if (name == L"Bullet") 
	{
		anims[L"IDLE"] = std::list<std::wstring>{
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
		anims[L"IDLE"] = std::list<std::wstring>{
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
		anims[L"IDLE"] = std::list<std::wstring>{
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
	if (name == L"Fog") {
		anims[L"IDLE"] = std::list<std::wstring>{
				L"assets\\fog\\g_fog_1.png",
				L"assets\\fog\\g_fog_2.png",
				L"assets\\fog\\g_fog_3.png",
		};
		auto sp  = std::make_shared<Sprite>(pos, rot, sizeX, sizeY, false, anims);
		sp->repeatOn(true);
		go = sp;
	}
	if (name == L"Dungeon Background") {
		anims[L"IDLE"] = std::list<std::wstring>{
				L"assets\\backgrounds\\battleback8.png",
		};
		auto sp  = std::make_shared<Sprite>(pos, rot, sizeX, sizeY, false, anims);
		go = sp;
	}

	if (name == L"Level Manager") {
		auto lm = LevelManager::getInstance();
		lm->Initialize();
		lm->Activate();
		lm->StartLevel();
		go = std::move(lm);
	}

	if (name == L"Star Background") {
		
	
	}
	if (name == L"Fire") {
		
	
	}
	
	go->Initialize();
	go->Activate();
	pObjectList.push_back(std::move(go));
	

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
	CheckCollisions();
}

void ObjectManager::RenderAll()
{


	for (auto& obj : this->pObjectList) {
		obj->Render();
	}

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

void ObjectManager::checkProximity(std::wstring objType1, std::wstring objType2, float threshold)
{
	if (objType1 == L"Zombies" && objType2 == L"Player") {
		auto list = QueryObjectList<Zombie>();
		auto p = QueryObject<Spaceship>();
		for (auto obj : list) {
			// FILL IN THE LIST IF PROXIM
			if (p && obj &&
				p->IsActive() && obj->IsActive()) {
				Vector2D disp = obj->getPos() - p->getPos();
				float magn = disp.magnitude();
				if (magn <= threshold) {
					obj->ProcessProximity(p);
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


