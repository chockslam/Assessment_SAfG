#pragma once
#include "vector2D.h"
#include "Shapes.h"
#include <string>
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
	virtual void Render();
	void wrap();

protected:

	float scale;

	Vector2D position;
	float posOffsetPower;
	
	float rotation;
	const float rotOffset = 1.0f;
	

	std::wstring path;
	int image;

	bool active;
};

