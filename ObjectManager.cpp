#include "ObjectManager.h"
#include "mydrawengine.h"

void ObjectManager::AddObject(std::unique_ptr<GameObject> object)
{
	this->pObjectList.push_back(std::move(object));
}

void ObjectManager::UpdateAll(float frameTime)
{
	for (auto& obj : this->pObjectList) {
		obj->Updated(frameTime);
	}
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
	this->pObjectList.clear();
}
