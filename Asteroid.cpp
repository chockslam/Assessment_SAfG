#include "Asteroid.h"
#include "mydrawengine.h"
#include <random>
#include "LevelManager.h"

Asteroid::Asteroid(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:
	CollidableObject::CollidableObject(initPos, rotation, scX, scY, activated, paths),
	velocity(vel)
{
	type = ObjectType::ASTEROID;
}

void Asteroid::Updated(float timeFrame)
{
	if (this->active)
	{
		this->velocity.setBearing(this->rotation, 200.0f);
		this->position += this->velocity * timeFrame;
		
		int width = 0;
		int height = 0;
		MyDrawEngine::GetInstance()->GetDimensions(this->image,height,width);
		this->boundingCircle.PlaceAt(this->position, this->scaleY * width / 2);
	}
	
	
}

IShape2D& Asteroid::GetShape()
{
	// TODO: insert return statement here
	return this->boundingCircle;
}

void Asteroid::ProcessCollision(std::shared_ptr<CollidableObject> other)
{
	if (other->GetType() == ObjectType::BULLET) {
		if (this->active) {
			this->Deactivate();
			LevelManager::getInstance()->EnemyDead();
		}
	}
}
