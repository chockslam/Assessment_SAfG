#include "Bullet.h"
#include "mydrawengine.h"
#include "ObjectManager.h"


#define BULLET_COOLDOWN 0.05f

Bullet::Bullet(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY , bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:
	CollidableObject::CollidableObject(initPos, rotation, scX, scY, activated, paths)
{
	animated = true;
	type = ObjectType::BULLET;
}

void Bullet::Updated(float timeFrame)
{
	if (this->active) {


		this->AnimUtilityUpdate(BULLET_COOLDOWN, timeFrame);


		this->velocity.setBearing(this->rotation, 1000.0f);
		this->position += this->velocity * timeFrame;
		
		

		int width = 0;
		int height = 0;
		MyDrawEngine::GetInstance()->GetDimensions(this->image, height, width);
	
		this->boundingRect.PlaceAt(Vector2D(this->position.XValue - width/2 * this->scaleY, this->position.YValue - height / 2 * this->scaleY), Vector2D(this->position.XValue + width / 2 * this->scaleY, this->position.YValue + height / 2 * this->scaleY));
	}
	
}



void Bullet::ProcessCollision(std::shared_ptr<CollidableObject> other)
{
	if (other->GetType() == ObjectType::ASTEROID) {
		if (this->active)
			this->Deactivate();
		ObjectManager::getInstance().Add(L"Puff", this->position, Vector2D(), this->rotation, this->scaleX/2.0f);
	}
}


IShape2D& Bullet::GetShape()
{
	// TODO: insert return statement here
	return this->boundingRect;
}
