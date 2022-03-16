#pragma once
#include <list>
#include <memory>
#include "GameObject.h"

class ObjectManager
{
public:
	ObjectManager();
	void Add(std::wstring name, Vector2D pos = { 0.0f, 0.0f }, Vector2D vel = { 0.0f, 0.0f }, float rot = 0.0f, float size = 1.0f, int appearance = 1, std::shared_ptr<ObjectManager> om = nullptr);
	void AddObject(std::unique_ptr<GameObject> object);
	void UpdateAll(float frameTime);
	void RenderAll();
	void DeleteAll();
	void DeleteInactive();
	void CheckCollisions();
	~ObjectManager();
private:
	std::list<std::unique_ptr<GameObject>> pObjectList;
};


