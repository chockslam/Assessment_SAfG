/*
	* Sprite .cpp file
	* 19012503
	* Aim of the class:		Represents any non-collidable sprite in the game world, i.e. background, foreground, etc. (functions implementation)
*/

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

/// <summary>
/// Update function.
/// </summary>
void Sprite::Updated(float timeFrame)
{
	if (this->active && this->animLooped) 
	{
		this->AnimUtilityUpdate(animTime, timeFrame);
	}
}

/// <summary>
/// Use it if you want sprite to be animated.
/// </summary>
/// <param name="flag">true if sprite is animated and looped, false otherwise</param>
/// <param name="customSpeed">speed of animation</param>
void Sprite::repeatOn(bool flag, float customSpeed)
{
	this->animLooped = flag;
	this->animTime = customSpeed;
}
