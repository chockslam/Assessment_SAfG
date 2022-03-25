#include "Character.h"

Character::Character(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:
	CollidableObject::CollidableObject(initPos, rotation, scX, scY, activated, paths),
	knocked(false),
	knockedTimer(-1.0f),
	health(1.0f)
{
}
