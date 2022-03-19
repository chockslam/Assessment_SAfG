#include "CollidableObject.h"

CollidableObject::CollidableObject(Vector2D initPos, float rotation, float sc, bool activated, std::wstring path)
	:
	GameObject::GameObject(initPos, rotation, sc, activated, path)
{
}
