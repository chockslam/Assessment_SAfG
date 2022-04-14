
/*
	* Power-up .cpp file
	* 19012503
	* Aim of the class:		Represents a power-up which supposed to grant player an ability on collision (function implementation).
*/

#include "PowerUp.h"
#include "mydrawengine.h"

// Animation speed of the power-up
#define ROT_SPEED 0.05f

PowerUp::PowerUp(Vector2D initPos, Vector2D velocity, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:
	CollidableObject::CollidableObject(initPos, rotation, scX, scY, activated, paths)
{
	this->type = ObjectType::POWER_UP;
	this->animTime = ROT_SPEED;
	this->animLooped = true;
	this->animated = true;
}

/// <summary>
/// Update function.
/// </summary>
void PowerUp::Updated(float timeFrame)
{
	if (this->active)
	{
		this->AnimUtilityUpdate(this->animTime, timeFrame);

		if (this->shapeExist) {
			int width = 0;
			int height = 0;
			MyDrawEngine::GetInstance()->GetDimensions(this->image, height, width);
			this->boundingCircle.PlaceAt(this->position, this->scaleY * width / 2);

		}
	}
}

/// <summary>
/// Collision with power-up handled in Hero class.
/// </summary>
void PowerUp::ProcessCollision(std::shared_ptr<CollidableObject> other)
{
}

/// <summary>
/// Returns collision shape.
/// </summary>
IShape2D& PowerUp::GetShape()
{
	return this->boundingCircle;
}
