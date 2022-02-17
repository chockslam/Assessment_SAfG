#pragma once
#include "vector2D.h"



class GameObject
{
public:

	GameObject(Vector2D initPos, float rotation, bool activated);
	virtual ~GameObject();
	void Activate();
	void Deactivate();
	virtual void Initialize() = 0;
	virtual void Updated() = 0;
protected:

	virtual void Render() = 0;

	Vector2D position;
	float posOffset;
	
	float rotation;
	float rotOffset;
	
	
	bool active;
};

