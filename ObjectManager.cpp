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

void ObjectManager::AddObject(std::shared_ptr<GameObject> obj)
{

	if (auto pt = std::dynamic_pointer_cast<LevelManager>(obj)) {
		//auto pt = std::dynamic_pointer_cast<LevelManager>(obj);


		this->lm = std::move(pt);
		this->lm->Initialize();
		this->lm->Activate();
		this->lm->StartLevel();
	}
	else {
		if (auto pt = std::dynamic_pointer_cast<CollidableObject>(obj)) {
			//auto pt = std::dynamic_pointer_cast<CollidableObject>(obj);
			pObjectCollidable.push_back(pt);
		}
			obj->Initialize();
			obj->Activate();
			pObjectList.push_back(std::move(obj));
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


