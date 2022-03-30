#pragma once
#include <list>
#include <memory>
#include "CollidableObject.h"
#include "LevelManager.h"

class ObjectManager
{
public:
    static ObjectManager& getInstance()
    {
        static ObjectManager    instance; // Guaranteed to be destroyed.
                              // Instantiated on first use.
        return instance;
    }
private:
    ObjectManager() {}                    // Constructor? (the {} brackets) are needed here.

    // C++ 11
    // =======
    // We can use the better technique of deleting the methods
    // we don't want.
public:
    ObjectManager(ObjectManager const&) = delete;
    void operator=(ObjectManager const&) = delete;

    // Note: Scott Meyers mentions in his Effective Modern
    //       C++ book, that deleted functions should generally
    //       be public as it results in better error messages
    //       due to the compilers behavior to check accessibility
    //       before deleted status
public:
	std::shared_ptr<LevelManager> getLevelManager() const { return this->lm; };
	void Add(std::wstring name, Vector2D pos = { 0.0f, 0.0f }, Vector2D vel = { 0.0f, 0.0f }, float rot = 0.0f, float sizeX = 1.0f, float sizeY = 1.0f, int appearance = 1); // ObjectFactory related method
	void AddObject(std::shared_ptr<GameObject> object);
	void UpdateAll(float frameTime);						// Update all objects in the pObjectList
	void RenderAll();										// Render all objects in the pObjectList
	void DeleteAll();										// Delete all objects in the pObjectList && pObjectCollidable
	void DeleteInactive();									// Delete all objects that became 'inactive'
	void InactivateAll();									// Delete all objects that became 'inactive'
	void CheckCollisions();									
	void checkOtherInteraction(std::wstring objType1, std::wstring objType2, float threshold);
	Vector2D getPosition(std::wstring objType);
	template<class T> std::shared_ptr<T> QueryObject();
	template<class T> std::list<std::shared_ptr<T>> QueryObjectList();
	~ObjectManager();
private:
	std::shared_ptr<LevelManager> lm;
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
template<class T>
inline std::list<std::shared_ptr<T>> ObjectManager::QueryObjectList()
{
	std::list<std::shared_ptr<T>> list;
	for (auto& pb : pObjectList)
		{
			if (auto pt = std::dynamic_pointer_cast<T>(pb))
			{
				list.push_back(pt);
			}
		}
		return list;
}
