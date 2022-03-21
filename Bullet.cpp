#include "Bullet.h"
#include "mydrawengine.h"
#include "ObjectManager.h"

Bullet::Bullet(Vector2D initPos, Vector2D vel, float rotation, float sc, bool activated, std::wstring path)
	:
	CollidableObject::CollidableObject(initPos, rotation, sc, activated, path),
	velocity(vel)
{
	type = ObjectType::BULLET;
}

void Bullet::Updated(float timeFrame)
{
	if (this->active) {
		this->velocity.setBearing(this->rotation, 10500.0f);
		this->position += this->velocity * timeFrame;
		
		timer -= timeFrame;
		if (timer <= 0) {
			this->active = false;
		}

		int width = 0;
		int height = 0;
		MyDrawEngine::GetInstance()->GetDimensions(this->image, height, width);
	
		this->boundingRect.PlaceAt(Vector2D(this->position.XValue - width/2 * this->scale, this->position.YValue - height / 2 * this->scale), Vector2D(this->position.XValue + width / 2 * this->scale, this->position.YValue + height / 2 * this->scale));
	}
	
}

void Bullet::ProcessCollision(std::shared_ptr<CollidableObject> other)
{
	if (other->GetType() == ObjectType::ASTEROID) {
		if (this->active)
			this->Deactivate();
		ObjectManager::getInstance().Add(L"Puff", this->position, Vector2D(), this->rotation, this->scale/2.0f);
	}
}


IShape2D& Bullet::GetShape()
{
	// TODO: insert return statement here
	return this->boundingRect;
}
