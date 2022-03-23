#include "Zombie.h"
#include "mydrawengine.h"
#include <random>
#include "LevelManager.h"


#define ZOMBIE_ANIM 0.1f

Zombie::Zombie(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:
	CollidableObject::CollidableObject(initPos, rotation, scX, scY, activated, paths),
	velocity(vel)
{
	type = ObjectType::ZOMBIE_WEAK;
	this->animLooped = true;
	this->animated = true;
}

void Zombie::Updated(float timeFrame)
{
	if (this->active)
	{
		this->AnimUtilityUpdate(ZOMBIE_ANIM, timeFrame);

		this->position += this->velocity * timeFrame;
		
		int width = 0;
		int height = 0;
		MyDrawEngine::GetInstance()->GetDimensions(this->image,height,width);
		width /= 2.3f;
		this->boundingRect.PlaceAt(Vector2D(this->position.XValue - width / 2 * this->scaleY, this->position.YValue - height / 2 * this->scaleY), Vector2D(this->position.XValue + width / 2 * this->scaleY, this->position.YValue + height / 2 * this->scaleY));
	}
	
	
}

IShape2D& Zombie::GetShape()
{
	// TODO: insert return statement here
	return this->boundingRect;
}

void Zombie::ProcessCollision(std::shared_ptr<CollidableObject> other)
{
	if (other->GetType() == ObjectType::BULLET) {
		if (this->active) {
			this->Deactivate();
			LevelManager::getInstance()->EnemyDead();
		}
	}

	
}

void Zombie::ProcessProximity(std::shared_ptr<GameObject> other)
{
	if (other->GetType() == ObjectType::SHIP) {
		if (this->active) {
			this->goTo(other->getPos());
		}
	}
}

void Zombie::goTo(Vector2D pos)
{
	this->currentAnimation = L"RUN";
	//float dot = Vector2D::dotProduct(pos, this->position);
	
	this->velocity = pos - this->position;
	if (this->velocity.XValue >= 0) {

		if (this->scaleX < 0)
			this->scaleX = -this->scaleX;
	}

	if (this->velocity.XValue < 0) {
		if (this->scaleX > 0)
			this->scaleX = -this->scaleX;
	}
}
