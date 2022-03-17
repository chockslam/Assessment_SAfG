#pragma once
#include "vector2D.h"
#include "Shapes.h"
#include <string>
#include "TypeGO.h"
#include <memory>

class GameObject
{
public:

	GameObject(Vector2D initPos, float rotation, float sc, bool activated, std::wstring path);
	virtual ~GameObject();
	bool IsActive() const;
	void Activate();
	void Deactivate();
	virtual void Initialize();
	virtual void Updated(float timeFrame) = 0;
	virtual IShape2D& GetShape() = 0;
	virtual void Render();
	virtual void ProcessCollision(std::shared_ptr<GameObject> other);
	const ObjectType GetType() { return this->type; };
	const bool GetCollidable() { return this->collidable; };

protected:

	ObjectType type = ObjectType::UNKNOWN;
	
	float scale;

	Vector2D position;
	float posOffsetPower;
	
	float rotation;
	const float rotOffset = 1.0f;
	

	std::wstring path;
	int image;

	bool active;
	bool collidable;
};

