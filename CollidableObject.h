#pragma once
#include "GameObject.h"
//#include "LevelManager.h"
#include "TypeGO.h"
class CollidableObject :
    public GameObject
{
public:
	CollidableObject(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);
	virtual void ProcessCollision(std::shared_ptr<CollidableObject> other) = 0;
	const ObjectType GetType() { return this->type; };
	virtual IShape2D& GetShape() = 0;
protected:
	ObjectType type = ObjectType::UNKNOWN;
//	std::shared_ptr<LevelManager> lm = nullptr;
};

