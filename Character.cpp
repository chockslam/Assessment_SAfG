/*
	* Character .cpp file
	* 19012503
	* Aim of the class: Represents any character - whether it is a player or zombie (functions implementation).
*/

#include "Character.h"
#include "AnimMasks.h"
#include "mydrawengine.h"

/// <summary>
/// Constructor
/// </summary>
Character::Character(Vector2D initPos, Vector2D velocity, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:
	CollidableObject::CollidableObject(initPos, rotation, scX, scY, activated, paths),
	knocked(false),
	attacking(false),
	knockedTimer(-1.0f),
	attackTimer(-1.0f),
	health(1.0f)
{
}

/// <summary>
/// Function to play animation once. facilitates states of a character.
/// </summary>
/// <param name="animName">Denotes wihich animation to play</param>
/// <param name="timeFrame">time frame parameter deducted from timer</param>
void Character::playAnimOnce(std::wstring animName, float timeFrame)
{
	if (animName == FALL) {
		if (knocked) {
			knockedTimer -= timeFrame;
			if (knockedTimer <= 0) {
				knocked = false;
				knockedTimer = anims[currentAnimation].size() * animTime;
			}
		}
	}
	if (animName == ATTACK) {
		if (attacking) {
			attackTimer -= timeFrame;
			if (attackTimer <= 0) {
				attacking = false;
				attackTimer = anims[currentAnimation].size() * animTime;
			}
		}
	}
}

/// <summary>
/// Function that facilitates the knock back of the character.
/// </summary>
/// <param name="power">power of knockback</param>
/// <param name="animSpeed">time of knockback animation (and state)</param>
/// <param name="otherObj"> optional pointer to the other object</param>
void Character::knockBack(float power, float animSpeed, std::shared_ptr<GameObject> otherObj)
{

	
		Vector2D acc;
		// -180 degrees
		float direction = -3.1415f / 2;
		// if other object is not nullptr, then knockback according to properties of otherObject
		// else knockback according to the scaleX parameter, i.e. where the character is looking currently.
		if (otherObj && (this->position - otherObj->getPos()).XValue > 0) {
			direction = -direction;
		}
		else
			if (this->scaleX < 0)
				direction = -direction;
		acc.setBearing(this->rotation + direction, this->AccPower);					// rotate acceleration vector with a constant utility parameter.
		this->velocity += acc * power;												// correct velocity vector
		this->knocked = true;														// set that the character is knocked
		this->animTime = animSpeed;													// set speed of the animation to be played.
		// knocked timer is set for the knocked animation to be played once.
		// it is presumed that currentAnimation is knocked animation.
		this->knockedTimer = anims[currentAnimation].size() * this->animTime;		// reset 'knocked timer'

}

/// <summary>
/// Restricts game world for the character.
/// Must be called in update.
/// </summary>
/// <param name="minY">Min characters position - y-axis</param>
/// <param name="minX">Min characters position - x-axis</param>
/// <param name="maxY">Max characters position - y-axis</param>
/// <param name="maxX">Max characters position - x-axis</param>
/// <param name="maxCameraX"> Max available camera position - x-axis </param>
/// <param name="minCameraX"> Min available camera position - x-axis </param>
/// <param name="trackedByCamera">whether the character is tracked by camera, supposed to be TRUE for the player</param>
void Character::RestrictMovement(int minY, int minX, int maxY, int maxX, int maxCameraX, int minCameraX, bool trackedByCamera)
{
	// Restrict movement across y-axis
	if (this->position.YValue <= minY) {
		this->position.YValue = minY;
	}
	else
	if (this->position.YValue >= maxY) {
		this->position.YValue = maxY;
	}

	// if object is tracked by camera handle camera placement and restrict x-position
	// else handle position restriction as usual
	// Supposed to be TRUE only for PLAYER.
	if (trackedByCamera) 
	{
		// (1) if minimum camera threshold is reached (characters's x-position is less than minimum camera threshold), 
		// place camera to its minimum position and check for players minimum x-position.
		// (2) else check for maximum camera threhold in the same fashion
		// (3) else track player's x-position with camera.
		if (this->position.XValue <= minCameraX) 
		{
			// restrict minimum x position of the character.
			if (this->position.XValue <= minX) 
			{
				this->position.XValue = minX;
			}
			// place camera to its minimum position.
			MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(minCameraX, 0));
		}
		else if (this->position.XValue >= maxCameraX) 
		{

			// restrict maximum x position of the character.
			if (this->position.XValue >= maxX) 
			{
				this->position.XValue = maxX;
			}

			// place camera to its maximum position.
			MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(maxCameraX, 0));
		}
		else 
		{
			// place camera to players x-position.
			MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(position.XValue, 0));
		}
	}
	else {
		if (this->position.XValue <= minX) {
			this->position.XValue = minX;
		}
		else if(this->position.XValue >= maxX){
			this->position.XValue = maxX;
		}
	}

	
}
