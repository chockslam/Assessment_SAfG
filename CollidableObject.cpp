#include "CollidableObject.h"

CollidableObject::CollidableObject(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:
	GameObject::GameObject(initPos, rotation, scX, scY, activated, paths),
	shapeExist(true)
{
}
