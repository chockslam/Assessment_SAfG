#include "Zombie.h"
#include "mydrawengine.h"
#include <random>
#include "LevelManager.h"


#define IDLE_Z_SPEED 0.1f
#define RUN_Z_SPEED 0.05f
#define KNOCK_Z_SPEED 0.1f
#define KNOCK_Z_POWER 5.0f

Zombie::Zombie(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:
	Character::Character(initPos, rotation, scX, scY, activated, paths),
	velocity(vel),
	level(1)
{
	type = ObjectType::ZOMBIE_WEAK;
	this->animLooped = true;
	this->animated = true;
	this->animTime = IDLE_Z_SPEED;
	this->health = 100;
	this->chasing = false;
}

void Zombie::setLevel(int level)
{
	this->level = level;
	if(this->level>0 && this->level<=5){
		this->type = ZOMBIE_WEAK;
	}
	if(this->level>5 && this->level<=10){
		this->type = ZOMBIE_NORMAL;
		this->scaleX *= 1.25f;
		this->scaleY *= 1.25f;
	}
	if(this->level>10 && this->level<=20){
		this->type = ZOMBIE_HARD;
		this->scaleX *= 1.5f;
		this->scaleY *= 1.5f;
	}
	this->health = 100 + this->level * 45;
}

void Zombie::Updated(float timeFrame)
{
	if (this->active)
	{
		this->AnimUtilityUpdate(animTime, timeFrame);
		
		if(this->chasing)
			this->position += this->velocity * timeFrame;
		
		if (knocked) {
			knockedTimer -= timeFrame;
			if (knockedTimer <= 0) {
				knocked = false;
				knockedTimer = anims[currentAnimation].size() * animTime;
			}
		}
		else {
			if(animLooped)
				currentAnimation = L"IDLE";
		}
		if (this->shapeExist) {
			int width = 0;
			int height = 0;
			MyDrawEngine::GetInstance()->GetDimensions(this->image, height, width);
			width /= 2.3f;
			this->boundingRect.PlaceAt(Vector2D(this->position.XValue - width / 2 * this->scaleY, this->position.YValue - height / 2 * this->scaleY), Vector2D(this->position.XValue + width / 2 * this->scaleY, this->position.YValue + height / 2 * this->scaleY));
		}
		// Process death
		if (this->health <= 0) {
			if (this->currentAnimation != L"DEATH" && this->animLooped)
				LevelManager::getInstance()->EnemyDead();
			currentAnimation = L"DEATH";
			this->shapeExist = false;
			this->animLooped = false;
		}

		// reset chasing
		this->chasing = false;
		
	}
	
	
}

IShape2D& Zombie::GetShape()
{
	return this->boundingRect;
}

void Zombie::ProcessCollision(std::shared_ptr<CollidableObject> other)
{
	if (other->GetType() == ObjectType::BULLET) {
		if (this->active) {
			currentAnimation = L"FALL";
			Vector2D acc;
			float direction = -3.1415f / 2;
			if (this->scaleX < 0)
				direction = -direction;
			acc.setBearing(this->rotation + direction, KNOCK_Z_POWER*100);
			this->velocity += acc * posOffsetPower;
			
			knocked = true;
			animTime = KNOCK_Z_SPEED;

			knockedTimer = anims[currentAnimation].size() * animTime;
			this->health -=40;
			
		}
	}

	
}

void Zombie::ProcessProximity(std::shared_ptr<GameObject> other)
{
	if (other->GetType() == ObjectType::SHIP) {
		if (this->active && other->IsActive()) {
			if (!knocked && animLooped) {
				this->goTo(other->getPos());
				this->chasing = true;
			}
		}
	}

}

void Zombie::goTo(Vector2D pos)
{
	this->currentAnimation = L"RUN";
	this->animTime = RUN_Z_SPEED;
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
