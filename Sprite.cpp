#include "Sprite.h"
#include "mydrawengine.h"

#define COOLDOWN 0.2f

Sprite::Sprite(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:	
	GameObject::GameObject(initPos, rotation, scX, scY, activated, paths)
{
	animated = true;
	animTime = COOLDOWN;
}

void Sprite::Updated(float timeFrame)
{
	if (this->active && this->animLooped) 
	{
		this->AnimUtilityUpdate(animTime, timeFrame);
	}
}

void Sprite::repeatOn(bool flag, float customSpeed)
{
	this->animLooped = flag;
	this->animTime = customSpeed;
}
