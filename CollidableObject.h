#pragma once
#include "GameObject.h"
//#include "LevelManager.h"
#include "TypeGO.h"
class CollidableObject :
    public GameObject
{
public:
	CollidableObject(Vector2D initPos, float rotation, float sc, bool activated, std::wstring path);
	virtual void ProcessCollision(std::shared_ptr<CollidableObject> other) = 0;
	const ObjectType GetType() { return this->type; };
	virtual IShape2D& GetShape() = 0;
protected:
	ObjectType type = ObjectType::UNKNOWN;
//	std::shared_ptr<LevelManager> lm = nullptr;
};

