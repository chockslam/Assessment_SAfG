#pragma once
#include "vector2D.h"
#include <string>

class GameObject
{
public:

	GameObject(Vector2D initPos, float rotation, bool activated, std::wstring path);
	virtual ~GameObject();
	void Activate();
	void Deactivate();
	virtual void Initialize();
	virtual void Updated() = 0;
protected:

	virtual void Render();

	Vector2D position;
	float posOffset;
	
	float rotation;
	float rotOffset;
	

	std::wstring path;
	int image;

	bool active;
};

