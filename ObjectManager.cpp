#include "ObjectManager.h"
#include "mydrawengine.h"
#include "Asteroid.h"
#include "Spaceship.h"
#include "Bullet.h"



ObjectManager::ObjectManager()
{
}

void ObjectManager::Add(std::wstring name, Vector2D pos, Vector2D vel, float rot, float size, int appearance, std::shared_ptr<ObjectManager> om)
{
	std::unique_ptr<GameObject> go;
	bool needOmInside = false;
	if (name == L"Asteroid") {
		std::wstring nameAss = L"assets\\rock" + std::to_wstring((appearance % 4) + 1) + L".bmp";
		go = std::make_unique<Asteroid>(pos, vel, rot, size, false, nameAss);
	}
	if (name == L"Random Flying Asteroid") {
		int i = rand() % 4;
		std::wstring nameAss = L"assets\\rock" + std::to_wstring((i % 4) + 1) + L".bmp";
		go = std::make_unique<Asteroid>(Vector2D(rand() % 600, rand() % 1200 - 600),
			Vector2D(rand() % 1000 + 50, rand() % 1000 + 50),
			rand() % 628 / 100.0f, 2.0f, false,
			nameAss);
	}
	if (name == L"Ship") {
		auto ship = std::make_unique<Spaceship>(pos, vel, rot, size, false);
		ship->Initialize(std::move(om));
		ship->Activate();
		pObjectList.push_back(std::move(ship));
		needOmInside = true;
	}
	if (name == L"Bullet") {
       		go = std::make_unique<Bullet>(pos, vel, rot, size, false, L"assets\\bullet.bmp");
		//pObjectList.push_back(std::move(go));
	}
	if (!needOmInside) {
		go->Initialize();
		go->Activate();
		pObjectList.push_back(std::move(go));
	}

}

void ObjectManager::AddObject(std::unique_ptr<GameObject> object)
{
	this->pObjectList.push_back(std::move(object));
}

void ObjectManager::UpdateAll(float frameTime)
{
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
	MyDrawEngine::GetInstance()->WriteInt(50, 50, pObjectList.size(),
		MyDrawEngine::GREEN);

}

void ObjectManager::DeleteAll()
{
	pObjectList.clear();
}

void ObjectManager::DeleteInactive()
{
	for (auto& obj : pObjectList) {
		if (!obj->IsActive())
			obj.release();
	}
	pObjectList.remove(NULL);
}

void ObjectManager::CheckCollisions() 
{
	std::list<std::unique_ptr<GameObject>>::iterator it1;
	std::list<std::unique_ptr<GameObject>>::iterator it2;
	for (it1 = pObjectList.begin(); it1 != pObjectList.end(); it1++)
	{
		for (it2 = std::next(it1); it2 != pObjectList.end(); it2++)
		{
			if ((*it1)->GetShape().Intersects((*it2)->GetShape())){

				// Do something
				//(*it2)->Deactivate();
			}
		}
	}

}

ObjectManager::~ObjectManager()
{
	if (!pObjectList.empty()) {
		pObjectList.clear();
	}
}


