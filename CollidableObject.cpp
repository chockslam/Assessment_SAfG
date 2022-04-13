#include "CollidableObject.h"
/*
	* Collidable Object .cpp file
	* 19012503
	* Aim of the class: Represents any 'Collidable' gameObject (constructor implementation).
*/

CollidableObject::CollidableObject(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:
	GameObject::GameObject(initPos, rotation, scX, scY, activated, paths),
	shapeExist(true)
{
}
