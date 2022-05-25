/*
	* Hero .cpp file
	* 19012503
	* Aim of the class:		Represents a playable hero, who is tracked by camera and controlled using keyboard (functions implementation).
*/

#include "Hero.h"
#include "mydrawengine.h"
#include "myinputs.h"
#include "mysoundengine.h"
#include "LevelManager.h"
#include "AnimMasks.h"


#include "ObjectFactory.h"

// #include "Bullet.h"

// ---- SOUND VOLUMES ------//
#define FIRE_SOUND -700
#define DEATH_SOUND -200
#define HURT_SOUND -1200
#define POWERED_SOUND -100
// ---- SOUND VOLUMES ------//


#define POWEREDUP_TIMER 5.0f

// ---- SOUND FILES ------//
#define FIREBALL_SOUND_FILE L"assets\\fire\\\sound_fireball\\fireball.wav"
#define DEATH_SOUND_FILE L"assets\\player\\\sounds\\death.wav"
#define HURT_SOUND_FILE L"assets\\player\\\sounds\\pain.wav"
#define POWERED_SOUND_FILE L"assets\\powerup\\\sounds\\pu.wav"
// ---- SOUND FILES ------//


// ---- ANIMATION SPEED ------//
#define IDLE_SPEED 0.08f
#define RUN_SPEED 0.1f
#define DEATH_SPEED 0.5f
#define ATTACK_SPEED 0.05f
#define KNOCKOUT_SPEED 0.05f
// ---- ANIMATION SPEED ------//

// knocout power -- dictates the distance the player is knocked.
#define KNOCKOUT_POWER 25.0f


// --- Zombie Damage based on the level of zombie.
#define W_Z_DAMAGE 100.0f
#define N_Z_DAMAGE 200.0f
#define H_Z_DAMAGE 300.0f

// frequency of shooting 
#define SHOOT_COOLDOWN 0.3f

// ---------- CONTRUCTORS WRITTEN FOR EXPERIMENTATION PURPOSES (NOT ALL OF THEM USED)------------------------------------------------------------------//
// ---------- CONTRUCTORS WRITTEN FOR EXPERIMENTATION PURPOSES (NOT ALL OF THEM USED)------------------------------------------------------------------//
// ---------- CONTRUCTORS WRITTEN FOR EXPERIMENTATION PURPOSES (NOT ALL OF THEM USED)------------------------------------------------------------------//

Hero::Hero(Vector2D initPos, Vector2D vel, float scX, float scY, float rotation, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:
	PlayableCharacter::PlayableCharacter(initPos,vel, rotation, scX, scY, activated, paths)
{
	// default parameters
	this->animLooped = true;
	this->animated = true;
	type = ObjectType::HERO;
	image = 0;
	animTime = IDLE_SPEED;
	this->maxHealth = 1200;
	this->health = this->maxHealth;
	this->invincTimer = -1.0f;
	this->frictionPower = 5.5f;
	this->shootCoolDown = SHOOT_COOLDOWN;
	this->poweredUpTimer = 0.0f;
	this->posOffsetPower = 30.0f;
}

Hero::Hero(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, bool activated)
	:
	Hero::Hero(initPos, vel, scX, scY, rotation, activated, std::unordered_map<std::wstring, std::list<std::wstring>>())
{
}

Hero::Hero(Vector2D initPos, Vector2D vel, float rotation)
	:
	Hero::Hero(initPos, vel, rotation, 5.0f,5.0f, false)
{
}

Hero::Hero(Vector2D initPos, Vector2D vel, bool activated)
	:
	Hero::Hero(initPos,vel,0.0f,5.0f,5.0f,activated)
{
}

Hero::Hero(Vector2D initPos, Vector2D vel)
	:
	Hero::Hero(initPos,vel, false)
{

}

Hero::Hero(Vector2D initPos)
	:
	Hero::Hero(initPos,Vector2D(1,0))
{
}

IShape2D& Hero::GetShape()
{
	return this->boundingCircle;
}

Hero::Hero()
	:
	Hero::Hero(Vector2D(0, 0))
{
}
// ---------- CONTRUCTORS WRITTEN FOR EXPERIMENTATION PURPOSES ------------------------------------------------------------------//
// ---------- CONTRUCTORS WRITTEN FOR EXPERIMENTATION PURPOSES ------------------------------------------------------------------//
// ---------- CONTRUCTORS WRITTEN FOR EXPERIMENTATION PURPOSES ------------------------------------------------------------------//

Hero::~Hero()
{
	
}
/// <summary>
/// Specfic Initialize function - load sounds.
/// </summary>
void Hero::Initialize()
{
	PlayableCharacter::Initialize();
	this->fireSound = MySoundEngine::GetInstance()->LoadWav(FIREBALL_SOUND_FILE);
	MySoundEngine::GetInstance()->SetVolume(this->fireSound, FIRE_SOUND);
	this->deathSound = MySoundEngine::GetInstance()->LoadWav(DEATH_SOUND_FILE);
	MySoundEngine::GetInstance()->SetVolume(this->fireSound, DEATH_SOUND);
	this->hurtSound = MySoundEngine::GetInstance()->LoadWav(HURT_SOUND_FILE);
	MySoundEngine::GetInstance()->SetVolume(this->fireSound, HURT_SOUND);
	this->poweredSound = MySoundEngine::GetInstance()->LoadWav(POWERED_SOUND_FILE);
	MySoundEngine::GetInstance()->SetVolume(this->poweredSound, POWERED_SOUND);
	
}



/// <summary>
/// Update function.
/// </summary>
void Hero::Updated(float timeFrame)
{

	if (this->active)
	{

		// Communicate state of the Hero object to the level manager, i.e. health information needed for health bar.
		ObjectFactory::getInstance().getLevelManager()->SetMaxHP(this->maxHealth);
		ObjectFactory::getInstance().getLevelManager()->SetHP(this->health);

		// if the player is running then make RUN animation be played faster. 
		if (this->posOffsetPower > 30.0f) {
			if (this->currentAnimation == RUN) {
				animTime = RUN_SPEED / 2;
			}
		}

		// update animation...
		this->AnimUtilityUpdate(animTime, timeFrame);
	

		// if the player is not knocked then,
		// check for attacking state and whether the level has started..
		if (!knocked && this->shapeExist) {
			// if player is not attacking, then go to IDLE state.
			if (!attacking) {
				currentAnimation = IDLE;
				animTime = IDLE_SPEED;
			}
			// The level started, then player can control, i.e use keyboard.
			if(ObjectFactory::getInstance().getLevelManager()->getStartTimer()<=0.0f)
				this->control(timeFrame);
		}

		// facilitate shooting frequency.
		if(this->shootCoolDown>=0.0f)
			shootCoolDown -= timeFrame;

		// knocked or attacking, then play animation
		// state of variables is handled in function itself.
		if(knocked)
			playAnimOnce(FALL, timeFrame);
		if(attacking)
			playAnimOnce(ATTACK, timeFrame);


		// if the player was hit and is invincible, then make object partially transfparent, while invincible
		if (this->invincTimer >= 0.0f) {
			this->alpha = 0.6f;
			this->invincTimer -= timeFrame;
		}
		else {
			this->alpha = 0.0f;
		}

		// powered up state faciliy
		if (this->poweredUpTimer >= 0.0f) {
			this->poweredUpTimer -= timeFrame;
		}

		// add friction to velocity.
		Vector2D friction = -(this->frictionPower) * this->velocity * timeFrame;
		this->velocity += friction;

		// restrict hero's movements with tracked camera.
		RestrictMovement(ObjectFactory::getInstance().getLevelManager()->getMinY(),
						 ObjectFactory::getInstance().getLevelManager()->getMinPlayerX(),
						 ObjectFactory::getInstance().getLevelManager()->getMaxY(),
						 ObjectFactory::getInstance().getLevelManager()->getMaxPlayerX(),
						 ObjectFactory::getInstance().getLevelManager()->getMaxCameraX(),
						 ObjectFactory::getInstance().getLevelManager()->getMinCameraX(),
						 true
						);

		// change position.
		this->position += this->velocity * timeFrame;
		

		// if shape exist then, place collision shape. with regards to the size of the image.
		if (this->shapeExist) {
			int width = 0;
			int height = 0;
			MyDrawEngine::GetInstance()->GetDimensions(this->image, height, width);
			this->boundingCircle.PlaceAt(this->position, this->scaleY * width / 2);

		}

		// process death.
		if (health <= 0) {
			// only if not dead yet then process death.
			if (this->currentAnimation != DEATH) {
				ObjectFactory::getInstance().getLevelManager()->PlayerDead();
				ObjectFactory::getInstance().AddUI( { 0.0f , 0.0f }, { 0.0f, 0.0f }, 0.0f, 10.0f, 10.0f, L"Dead Screen");
				currentAnimation = DEATH;
				this->shapeExist = false;
				this->animLooped = false;
				this->animTime = DEATH_SPEED;
				MySoundEngine::GetInstance()->Play(this->deathSound);
			}
		}
		
		
	}

}

/// <summary>
/// Collidable object specific facility implemented for hero.
/// </summary>
void Hero::ProcessCollision(std::shared_ptr<CollidableObject> other)
{
	if (this->active) {
		if (other->DoesShapeExist()) {
			// process collision with zombies AND POWER-UPS only if player is not invincible
			if (this->invincTimer<=0.0f) {

				if (other->GetType() == ObjectType::ZOMBIE_WEAK) {

					this->currentAnimation = FALL;
					this->knockBack(KNOCKOUT_POWER/2, KNOCKOUT_SPEED, other);
					invincTimer = knockedTimer * 3;
					this->health -= W_Z_DAMAGE;

					MySoundEngine::GetInstance()->Play(this->hurtSound);
				}
				if (other->GetType() == ObjectType::ZOMBIE_NORMAL) {

					this->currentAnimation = FALL;
					this->knockBack(KNOCKOUT_POWER, KNOCKOUT_SPEED, other);
					invincTimer = knockedTimer * 3;
					this->health -= N_Z_DAMAGE;

					MySoundEngine::GetInstance()->Play(this->hurtSound);
				}
				if (other->GetType() == ObjectType::ZOMBIE_HARD) {

					this->currentAnimation = FALL;
					this->knockBack(KNOCKOUT_POWER, KNOCKOUT_SPEED, other);
					invincTimer = knockedTimer * 3;
					this->health -= H_Z_DAMAGE;

					MySoundEngine::GetInstance()->Play(this->hurtSound);
					
				}
				if (other->GetType() == ObjectType::POWER_UP) {

					other->Deactivate();
					this->poweredUpTimer = POWEREDUP_TIMER;

					MySoundEngine::GetInstance()->Play(this->poweredSound);
				}


			}
		}
	}

	
}

/// <summary>
/// Control Function.
/// </summary>
/// <param name="timeFrame"> frame time from update function.</param>
/// <param name="up"> go up key </param>
/// <param name="left"> go left key </param>
/// <param name="down"> go down key </param>
/// <param name="right"> go right key </param>
/// <param name="run"> run key </param>
/// <param name="shoot"> shoot key </param>
void Hero::control(float timeFrame, int up, int left, int down, int right, int run, int shoot)
{
	MyInputs::GetInstance()->SampleKeyboard();

	// Handle speed
	if (MyInputs::GetInstance()->KeyPressed(run))
	{
		this->posOffsetPower = 50.0f;
		
	}
	else {
		this->posOffsetPower = 30.0f;
	}
	// ------------------ DIRECTIONAL MOVEMENT CONTROL -----------------------------//
	if (MyInputs::GetInstance()->KeyPressed(up))
	{
		Vector2D acc;
		acc.setBearing(this->rotation, this->AccPower);
		this->velocity += acc * timeFrame * posOffsetPower;
		// if not attacking then chamge animation 
		if (!this->attacking) {
			currentAnimation = RUN;
			animTime = RUN_SPEED;
		}

	}
	if (MyInputs::GetInstance()->KeyPressed(down))
	{

		Vector2D acc;
		acc.setBearing(this->rotation + 3.1415f, this->AccPower);
		this->velocity += acc * timeFrame * posOffsetPower;
		if (!this->attacking) {
			currentAnimation = RUN;
			animTime = RUN_SPEED;
		}


	}
	if (MyInputs::GetInstance()->KeyPressed(right))
	{

		if (this->scaleX < 0)
			this->scaleX = -this->scaleX;
		Vector2D acc;
		acc.setBearing(this->rotation + 3.1415f / 2, this->AccPower);
		this->velocity += acc * timeFrame * posOffsetPower;
		if (!this->attacking) {
			currentAnimation = RUN;
			animTime = RUN_SPEED;
		}


	}
	if (MyInputs::GetInstance()->KeyPressed(left))
	{

		if (this->scaleX >= 0)
			this->scaleX = -this->scaleX;
		Vector2D acc;
		acc.setBearing(this->rotation - 3.1415f / 2, this->AccPower);
		this->velocity += acc * timeFrame * posOffsetPower;
		if (!this->attacking) {
			currentAnimation = RUN;
			animTime = RUN_SPEED;
		}


	}
	// ------------------ DIRECTIONAL MOVEMENT CONTROL -----------------------------//

	// Shoot only if not dead, i.e. shape exists == true, and shooting cooldown variable reached 0f.
	if (MyInputs::GetInstance()->NewKeyPressed(shoot)&&this->shapeExist&&this->shootCoolDown<=0.0f)
	{
		// handle state transition.
		this->attacking = true;
		this->currentAnimation = ATTACK;
		this->animTime = ATTACK_SPEED;
		this->attackTimer = anims[currentAnimation].size() * animTime;

		// handle rotation/direction of the bullet to be shot at.
		// It depends on the ScaleX parameter, i.e. where the player is looking at currently.
		float rotation = this->rotation;
		if (this->scaleX < 0) {
			rotation = this->rotation + 3.1415f;
		}
		MySoundEngine::GetInstance()->Play(this->fireSound);
		
		// if the player is powered-up then emit strong bullet.
		if (this->poweredUpTimer > 0.0f) {
			ObjectFactory::getInstance().AddBullet(this->position, this->velocity, rotation + 3.1415f / 2, this->scaleX * 2, -this->scaleY * 2, L"Strong");
		}
		else {
			ObjectFactory::getInstance().AddBullet( this->position, this->velocity, rotation + 3.1415f / 2, this->scaleX * 2, -this->scaleY * 2);
		}
		// reset cooldown.
		this->shootCoolDown = SHOOT_COOLDOWN;
	}

	

}

