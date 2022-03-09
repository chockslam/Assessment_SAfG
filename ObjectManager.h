#pragma once
#include <list>
#include <memory>
#include "GameObject.h"

class ObjectManager
{
public:
	void AddObject(std::unique_ptr<GameObject> object);
	void UpdateAll(float frameTime);
	void RenderAll();
	void DeleteAll();
private:
	std::list<std::unique_ptr<GameObject>> pObjectList;
};

