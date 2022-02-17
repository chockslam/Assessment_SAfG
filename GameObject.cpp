#include "GameObject.h"
#include "ErrorLogger.h"

GameObject::GameObject(Vector2D initPos)
	: GameObject::GameObject(initPos, false)
{
}

GameObject::GameObject(Vector2D initPos, float rotation)
	:
	GameObject::GameObject(initPos, rotation, false)
{
}


GameObject::GameObject(Vector2D initPos, float rotation, bool activated)
	:
	position(initPos),
	rotation(rotation),
	active(activated)
{
}

GameObject::GameObject(float rotation, bool activated)
	:
	GameObject::GameObject(Vector2D(0,0), rotation, activated)
{
}

GameObject::GameObject(Vector2D initPos, bool activated)
	:
	GameObject::GameObject(initPos, 0.0f, activated)
{

}

GameObject::GameObject()
	: 
	GameObject::GameObject(Vector2D(0,0))
{

}

GameObject::~GameObject()
{
}

void GameObject::Activate()
{
	if (!active) {
		active = true;
	}
	else {
		ErrorLogger::Writeln(L"The object is already activated");
	}
}

void GameObject::Deactivate()
{
	if (active) {
		active = false;
	}
	else {
		ErrorLogger::Writeln(L"The object is already deativated");
	}
}

void GameObject::Initialize()
{
}

void GameObject::Updated()
{
}

