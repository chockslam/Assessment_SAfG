#include "ObjectManager.h"
#include "mydrawengine.h"
#include "Asteroid.h"
#include "Spaceship.h"
#include "Explosion.h"
#include "LevelManager.h"
#include "Bullet.h"
#include <iostream>
#include <string>


ObjectManager::ObjectManager()
{
}

void ObjectManager::Add(std::wstring name, Vector2D pos, Vector2D vel, float rot, float size, int appearance, std::shared_ptr<ObjectManager> om)
{
	std::shared_ptr<GameObject> go;
	std::shared_ptr<CollidableObject> cgo;
	bool needOmInside = false;
	//bool lmExists = false;
	//LevelManager* lm;
	//std::shared_ptr<LevelManager> lm;



	

	if (name == L"Asteroid") 
	{
		std::wstring nameAss = L"assets\\rock" + std::to_wstring((appearance % 4) + 1) + L".bmp";
		cgo = std::make_shared<Asteroid>(pos, vel, rot, size, false, nameAss);
		pObjectCollidable.push_back(cgo);
		go = cgo;
	}
	if (name == L"Random Flying Asteroid") 
	{
		int i = rand() % 4;
		std::wstring nameAss = L"assets\\rock" + std::to_wstring((i % 4) + 1) + L".bmp";
		cgo = std::make_shared<Asteroid>(Vector2D(rand() % 600, rand() % 1200 - 600),
			Vector2D(rand() % 1000 + 50, rand() % 1000 + 50),
			rand() % 628 / 100.0f, 2.0f, false,
			nameAss);
		pObjectCollidable.push_back(cgo);
		go = cgo;

	}
	if (name == L"Ship") 
	{
		auto ship = std::make_shared<Spaceship>(pos, vel, rot, size, false);
		ship->Initialize(std::move(om));
		ship->Activate();
		pObjectCollidable.push_back(ship);
		pObjectList.push_back(std::move(ship));
		needOmInside = true;
	}
	if (name == L"Bullet") 
	{
		auto bul = std::make_shared<Bullet>(pos, vel, rot, size, false, L"assets\\bullet.bmp");
		
		bul->Initialize(std::move(om));
		bul->Activate();
		
		pObjectCollidable.push_back(bul);
		pObjectList.push_back(std::move(bul));
		needOmInside = true;

	}

	if (name == L"Explosion") {
		go = std::make_shared<Explosion>(pos, rot, size, false,
			std::list<std::wstring>{
				L"assets\\explosion1.bmp",
				L"assets\\explosion2.bmp",
				L"assets\\explosion3.bmp",
				L"assets\\explosion4.bmp",
				L"assets\\explosion5.bmp",
				L"assets\\explosion6.bmp",
				L"assets\\explosion7.bmp",
				L"assets\\explosion8.bmp"
		});
		
	}
	if (name == L"Puff") {
		go = std::make_shared<Explosion>(pos, rot, size, false,
			std::list<std::wstring>{
				L"assets\\puff1.bmp",
				L"assets\\puff2.bmp",
				L"assets\\puff3.bmp",
				L"assets\\puff4.bmp",
				L"assets\\puff5.bmp",
				L"assets\\puff6.bmp",
				L"assets\\puff7.bmp",
				L"assets\\puff8.bmp"
		});
		
	}

	if (name == L"Level Manager") {
		auto lm = LevelManager::getInstance();
		lm->Initialize(om);
		//lm->Initialize(std::move(om));
		lm->Activate();
		lm->StartLevel();
		pObjectList.push_back(std::move(lm));
	
		needOmInside = true;
	}

	
	if (!needOmInside) 
	{
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
			(*it1)->IsActive()) 
		{
			for (it2 = std::next(it1); it2 != pObjectCollidable.end(); it2++)
			{
				if ((*it2) &&
					(*it2)->IsActive() &&
					(*it1)->GetShape().Intersects((*it2)->GetShape())) 
				{
					(*it1)->ProcessCollision(*it2);
					(*it2)->ProcessCollision(*it1);
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


