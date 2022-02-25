#include "Rock.h"

Rock::Rock(Vector2D initPos, Vector2D vel, float rotation, bool activated, std::wstring path)
	:
	GameObject::GameObject(initPos, rotation, activated, path)
{
}

void Rock::Updated(float timeFrame)
{
	this->Render();
}
