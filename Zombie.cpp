/*
	* Zombie .h file
	* 19012503
	* Aim of the class:		Represents an Enemy - Zombie. Zombie can be WEAK, NORMAL,HARD.
*/

#include "Zombie.h"
#include "mysoundengine.h"
#include "mydrawengine.h"
#include <random>
#include "ObjectFactory.h"
#include "AnimMasks.h"


#define VISUAL_BUG_FIXING_MACRO_TO_STOP_FLIPPING_IMAGE 10.0f // Just a Visual Bug Fixing Macro...


//-------------------------------------- ZOMBIE'S DEATH AND HURT SOUNDS VOLUME ------------------------------------------//
#define DEATH_VOLUME -100
#define ROAR_VOLUME -1000
//-------------------------------------- ZOMBIE'S DEATH AND HURT SOUNDS VOLUME ------------------------------------------//



//-------------------------------------- ZOMBIE'S DEATH AND HURT SOUNDS DEPENDING ON ZOMBIES LEVEL ------------------------------------------//
#define WEAK_ZOMBIE_DEATH_SOUND  L"assets\\enemies\\sounds\\Death3.wav"
#define NORMAL_ZOMBIE_DEATH_SOUND  L"assets\\enemies\\sounds\\Death2.wav"
#define HARD_ZOMBIE_DEATH_SOUND  L"assets\\enemies\\sounds\\Death.wav"
#define WEAK_ZOMBIE_ROAR_SOUND  L"assets\\enemies\\sounds\\Roar1.wav"
#define NORMAL_ZOMBIE_ROAR_SOUND  L"assets\\enemies\\sounds\\Roar2.wav"
#define HARD_ZOMBIE_ROAR_SOUND  L"assets\\enemies\\sounds\\Roar3.wav"
//-------------------------------------- ZOMBIE'S DEATH AND HURT SOUNDS DEPENDING ON ZOMBIES LEVEL ------------------------------------------//




//-------------------------------------- VARIOUS SPEED OF VARIOUS ANIMATIONS ------------------------------------------//
#define IDLE_Z_SPEED 0.1f
#define RUN_Z_SPEED 0.05f
#define KNOCK_Z_SPEED 0.2f
#define ATTACK_Z_SPEED 0.025f
//-------------------------------------- VARIOUS SPEED OF VARIOUS ANIMATIONS ------------------------------------------//

// HOW FAR ZOMBIE IS KNOCKED.
#define KNOCK_Z_POWER 5.0f


// constructor
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


/// <summary>
/// Set level of the zombies.
/// Level Dictates:
///		whether the zombies WEAK, NORMAL, HARD,
///		health of the zombie,
///		sounds
/// </summary>
/// <param name="level">Level of the zombie</param>
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

/// <summary>
/// Update function.
/// </summary>
/// <param name="timeFrame"></param>
void Zombie::Updated(float timeFrame)
{
	if (this->active)
	{
		this->AnimUtilityUpdate(animTime, timeFrame);
		
		// Apply friction.
		Vector2D friction = -(this->frictionPower) * this->velocity * timeFrame;
		this->velocity += friction;
		// Restric movements without 'camera tracked' option.
		RestrictMovement(
			ObjectFactory::getInstance().getLevelManager()->getMinY(),
			ObjectFactory::getInstance().getLevelManager()->getMinPlayerX(),
			ObjectFactory::getInstance().getLevelManager()->getMaxY(),
			ObjectFactory::getInstance().getLevelManager()->getMaxPlayerX()
		);
		// change position
		this->position += this->velocity * timeFrame;

		// Process knocked and attacking states
		if (knocked)
  			playAnimOnce(FALL, timeFrame);
		if (attacking)
			playAnimOnce(ATTACK, timeFrame);

		// if not knocked/attacking/dying then go to idle animation.
		if(!this->knocked && !this->attacking && this->currentAnimation!=DEATH)
		{
				this->currentAnimation = IDLE;
				this->animTime = IDLE_Z_SPEED;
		}

		// place collision shape, if it is applicable.
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
				this->currentAnimation = DEATH;
				this->shapeExist = false;
				this->animLooped = false;
				ObjectFactory::getInstance().getLevelManager()->EnemyDead();
			}
			
		}

		
	}
	
	
}
/// <summary>
/// Returns collision shape
/// </summary>
IShape2D& Zombie::GetShape()
{
	return this->boundingRect;
}

/// <summary>
/// Process Collision function.
/// </summary>
/// <param name="other"></param>
void Zombie::ProcessCollision(std::shared_ptr<CollidableObject> other)
{

	// If it is any type of bullet - play hurt sound, change animation to FALL, Process knockback, deduct health depending on the Bullet Type.

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
	
	// If it is collided with hero - play Attacking animation
	if (other->GetType() == ObjectType::HERO) {
		if (this->active) {
			
			this->currentAnimation = ATTACK;
			this->attacking = true;
			this->animTime = ATTACK_Z_SPEED;
			this->attackTimer = anims[currentAnimation].size() * animTime;
		}
	}

	
}
/// <summary>
/// Processes Proximity of the zombie to the player.
/// If player is close enough - chase player.
/// </summary>
/// <param name="other">other object</param>
/// <param name="dist"> current distance. </param>
/// <param name="maxDist"> max distance to other objects (the threshold, when the function is called) </param>
void Zombie::ProcessProximity(std::shared_ptr<GameObject> other, float dist, float maxDist)
{
	if (other->GetType() == ObjectType::HERO) {

		if (this->active && other->IsActive()) {
			if (!knocked && !attacking && animLooped) {
				
				// flag where to chase or not
				bool chase = false;
				
				// decide whether the zombies can chase based the player based on their type and relative (to threshold) distance.
				// The 'harder' zomies is, the more aware of the player he is, i.e. harder zombies can notice player from farer away the farer away 

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

				// flag was set to true, then chase player.
				if(chase)
					this->goTo(other->getPos());
			}
		}
	}

}

/// <summary>
/// Zombie 'dumb' 'go to' controller.
/// </summary>
/// <param name="pos"> Where zombie need to go </param>
void Zombie::goTo(Vector2D pos)
{
	// change to RUN animation/state
	this->currentAnimation = RUN;
	this->animTime = RUN_Z_SPEED;
	
	// find disposition vector
	Vector2D dispos = pos - this->position;
	
	// essentialy a velocity vector, pointing to pos.
	// Facilitates constant speed.
	Vector2D disposConstLength = (pos - this->position).unitVector() * 400;


	// The harder zombies is, the faster he is.
	if (this->type == ZOMBIE_NORMAL) {
		this->animTime /= 1.4f;
		disposConstLength *= 1.5f;
	}
	if (this->type == ZOMBIE_HARD) {
		this->animTime /= 1.7f;
		disposConstLength *= 2.0f;
	}

	// apply new velocity vector.
	this->velocity = disposConstLength;

	//stop flipping image when zombies are to close to the player, after he is dead. HARDCODED = bad, sorry.
	if (dispos.magnitude() >= VISUAL_BUG_FIXING_MACRO_TO_STOP_FLIPPING_IMAGE) {

		// Decides where zombies is looking, based on his velocity vector's x value.

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
