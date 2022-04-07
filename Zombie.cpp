#include "Zombie.h"
#include "mysoundengine.h"
#include "mydrawengine.h"
#include <random>
#include "ObjectManager.h"
#include "AnimMasks.h"

#define DEATH_VOLUME -100
#define ROAR_VOLUME -1000
#define VISUAL_BUG_FIXING_MACRO_TO_STOP_FLIPPING_IMAGE 10.0f

#define WEAK_ZOMBIE_DEATH_SOUND  L"assets\\enemies\\sounds\\Death3.wav"
#define NORMAL_ZOMBIE_DEATH_SOUND  L"assets\\enemies\\sounds\\Death2.wav"
#define HARD_ZOMBIE_DEATH_SOUND  L"assets\\enemies\\sounds\\Death.wav"
#define WEAK_ZOMBIE_ROAR_SOUND  L"assets\\enemies\\sounds\\Roar1.wav"
#define NORMAL_ZOMBIE_ROAR_SOUND  L"assets\\enemies\\sounds\\Roar2.wav"
#define HARD_ZOMBIE_ROAR_SOUND  L"assets\\enemies\\sounds\\Roar3.wav"

#define IDLE_Z_SPEED 0.1f
#define RUN_Z_SPEED 0.05f
#define KNOCK_Z_SPEED 0.2f
#define KNOCK_Z_POWER 5.0f
#define ATTACK_Z_SPEED 0.025f

Zombie::Zombie(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:
	Character::Character(initPos, vel, rotation, scX, scY, activated, paths),
	level(1)
{
	type = ObjectType::ZOMBIE_WEAK;
	this->animLooped = true;
	this->animated = true;
	this->animTime = IDLE_Z_SPEED;
	this->health = 100;
	this->frictionPower = 3.5f;
	//this->chasing = false;
}

void Zombie::setLevel(int level)
{
	this->level = level;
	if(this->level>=0 && this->level<=5){
		this->type = ZOMBIE_WEAK;
		this->deathSound = MySoundEngine::GetInstance()->LoadWav(WEAK_ZOMBIE_DEATH_SOUND);
		this->hurtSound = MySoundEngine::GetInstance()->LoadWav(WEAK_ZOMBIE_ROAR_SOUND);
	}
	if(this->level>5 && this->level<=10){
		this->type = ZOMBIE_NORMAL;
		this->scaleX *= 1.25f;
		this->scaleY *= 1.25f;
		this->deathSound = MySoundEngine::GetInstance()->LoadWav(NORMAL_ZOMBIE_DEATH_SOUND);
		this->hurtSound = MySoundEngine::GetInstance()->LoadWav(NORMAL_ZOMBIE_ROAR_SOUND);
	}
	if(this->level>10 && this->level<=20){
		this->type = ZOMBIE_HARD;
		this->scaleX *= 1.4f;
		this->scaleY *= 1.4f;
		this->deathSound = MySoundEngine::GetInstance()->LoadWav(HARD_ZOMBIE_DEATH_SOUND);
		this->hurtSound = MySoundEngine::GetInstance()->LoadWav(HARD_ZOMBIE_ROAR_SOUND);
	}
	MySoundEngine::GetInstance()->SetVolume(this->deathSound,	DEATH_VOLUME);
	MySoundEngine::GetInstance()->SetVolume(this->hurtSound,	ROAR_VOLUME);

	this->health = 100 + this->level * 10;
}

void Zombie::Updated(float timeFrame)
{
	if (this->active)
	{
		this->AnimUtilityUpdate(animTime, timeFrame);
		
		//if(this->chasing)
		Vector2D friction = -(this->frictionPower) * this->velocity * timeFrame;
		this->velocity += friction;
		RestrictMovement(ObjectManager::getInstance().getLevelManager()->getMinY(),
			ObjectManager::getInstance().getLevelManager()->getMinPlayerX(),
			ObjectManager::getInstance().getLevelManager()->getMaxY(),
			ObjectManager::getInstance().getLevelManager()->getMaxPlayerX()
		);
		this->position += this->velocity * timeFrame;

		if (knocked)
  			playAnimOnce(FALL, timeFrame);
		if (attacking)
			playAnimOnce(ATTACK, timeFrame);

		if(!this->knocked && !this->attacking && this->currentAnimation!=DEATH)
		{
				this->currentAnimation = IDLE;
				this->animTime = IDLE_Z_SPEED;
		}
		if (this->shapeExist) {
			int width = 0;
			int height = 0;
			MyDrawEngine::GetInstance()->GetDimensions(this->image, height, width);
			width /= 2.7f;
			this->boundingRect.PlaceAt(Vector2D(this->position.XValue - width / 2 * this->scaleY, this->position.YValue - height / 2 * this->scaleY), Vector2D(this->position.XValue + width / 2 * this->scaleY, this->position.YValue + height / 2 * this->scaleY));
		}
		// Process death
		if (this->health <= 0) {
			if (this->currentAnimation != DEATH) {
				MySoundEngine::GetInstance()->Play(this->deathSound);
				currentAnimation = DEATH;
				this->shapeExist = false;
				this->animLooped = false;
				ObjectManager::getInstance().getLevelManager()->EnemyDead();
			}
			
		}

		
	}
	
	
}

IShape2D& Zombie::GetShape()
{
	return this->boundingRect;
}

void Zombie::ProcessCollision(std::shared_ptr<CollidableObject> other)
{
	if (other->GetType() == ObjectType::FIRE) {
		if (this->active) {
			MySoundEngine::GetInstance()->Play(this->hurtSound);
			this->currentAnimation = FALL;
			this->knockBack(KNOCK_Z_POWER / 2, KNOCK_Z_SPEED, other);
			this->health -= 40;
			
		}
	}
	if (other->GetType() == ObjectType::FIRE_STRONG) {
		if (this->active) {
			MySoundEngine::GetInstance()->Play(this->hurtSound);
			this->currentAnimation = FALL;
			this->knockBack(KNOCK_Z_POWER / 2, KNOCK_Z_SPEED, other);
			this->health -= 120;
			
		}
	}

	if (other->GetType() == ObjectType::SHIP) {
		if (this->active) {
			
			this->currentAnimation = ATTACK;
			this->attacking = true;
			this->animTime = ATTACK_Z_SPEED;
			this->attackTimer = anims[currentAnimation].size() * animTime;
		}
	}

	
}

void Zombie::ProcessProximity(std::shared_ptr<GameObject> other, float dist, float maxDist)
{
	if (other->GetType() == ObjectType::SHIP) {

		if (this->active && other->IsActive()) {
			if (!knocked && !attacking && animLooped) {
				//if(this->type == ZOMBIE_WEAK)
				bool chase = false;
				if (dist / maxDist < 0.5f) {
					if (this->type == ObjectType::ZOMBIE_WEAK)
						chase = true;
				}
				
				if (dist / maxDist < 0.7f) {
					if (this->type == ObjectType::ZOMBIE_NORMAL)
						chase = true;
				}
				
				if (this->type == ObjectType::ZOMBIE_HARD)
					chase = true;

				if(chase)
					this->goTo(other->getPos());
			}
		}
	}

}

void Zombie::goTo(Vector2D pos)
{
	this->currentAnimation = RUN;
	this->animTime = RUN_Z_SPEED;
	
	Vector2D dispos = pos - this->position;
	Vector2D disposConstLength = (pos - this->position).unitVector() * 400;

	if (this->type == ZOMBIE_NORMAL) {
		this->animTime /= 1.4f;
		disposConstLength *= 1.5f;
	}
	if (this->type == ZOMBIE_HARD) {
		this->animTime /= 1.7f;
		disposConstLength *= 2.0f;
	}

	this->velocity = disposConstLength;

	//stop flipping image when zombies are to close to you. HARDCODED = bad, sorry.
	if (dispos.magnitude() >= VISUAL_BUG_FIXING_MACRO_TO_STOP_FLIPPING_IMAGE) {
		if (this->velocity.XValue >= 0) {

			if (this->scaleX < 0)
				this->scaleX = -this->scaleX;
		}
		if (this->velocity.XValue < 0) {
			if (this->scaleX > 0)
				this->scaleX = -this->scaleX;
		}
	}
	
	

}
