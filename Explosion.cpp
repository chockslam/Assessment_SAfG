#include "Explosion.h"
#include "mydrawengine.h"

#define COOLDOWN 0.1f

Explosion::Explosion(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:	
	GameObject::GameObject(initPos, rotation, scX, scY, activated, paths)
{
	animated = true;
	coolDownAnim = COOLDOWN;
}

void Explosion::Updated(float timeFrame)
{
	if (this->active) 
	{
		this->AnimUtilityUpdate(COOLDOWN, timeFrame);
	}
}
