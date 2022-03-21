#pragma once
#include <list>
#include <memory>
#include "CollidableObject.h"

class ObjectManager
{

public:
	ObjectManager(); 
	void Add(std::wstring name, Vector2D pos = { 0.0f, 0.0f }, Vector2D vel = { 0.0f, 0.0f }, float rot = 0.0f, float size = 1.0f, int appearance = 1, std::shared_ptr<ObjectManager> om = nullptr); // ObjectFactory related method
	void AddObject(std::shared_ptr<GameObject> object);
	void UpdateAll(float frameTime);						// Update all objects in the pObjectList
	void RenderAll();										// Render all objects in the pObjectList
	void DeleteAll();										// Delete all objects in the pObjectList && pObjectCollidable
	void DeleteInactive();									// Delete all objects that became 'inactive'
	void CheckCollisions();
	template<class T> std::shared_ptr<T> QueryObject();
	~ObjectManager();
private:
	std::list<std::shared_ptr<GameObject>> pObjectList;
	std::list<std::shared_ptr<CollidableObject>> pObjectCollidable;
};

template<class T>
inline std::shared_ptr<T> ObjectManager::QueryObject()
{
	for (auto& pb : pObjectList)
		{
			if (auto pt = std::dynamic_pointer_cast<T>(pb))
			{
				return pt;
			}
		}
		return nullptr;
}
