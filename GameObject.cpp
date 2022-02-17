#include "GameObject.h"
#include "ErrorLogger.h"


GameObject::GameObject(Vector2D initPos, float rotation, bool activated)
	:
	position(initPos),
	rotation(rotation),
	active(activated)
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

