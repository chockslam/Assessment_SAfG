#include "PowerUp.h"
#include "mydrawengine.h"

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

void PowerUp::ProcessCollision(std::shared_ptr<CollidableObject> other)
{
}

IShape2D& PowerUp::GetShape()
{
	return this->boundingCircle;
}
