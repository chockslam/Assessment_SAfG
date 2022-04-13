#include "Hero.h"


#include "mydrawengine.h"
#include "myinputs.h"
#include "mysoundengine.h"
#include "LevelManager.h"
#include "AnimMasks.h"


#include "ObjectManager.h"

// #include "Bullet.h"

#define FIRE_SOUND -700
#define DEATH_SOUND -200
#define HURT_SOUND -1200
#define POWERED_SOUND -100

#define POWEREDUP_TIMER 5.0f

#define FIREBALL_SOUND_FILE L"assets\\fire\\\sound_fireball\\fireball.wav"
#define DEATH_SOUND_FILE L"assets\\player\\\sounds\\death.wav"
#define HURT_SOUND_FILE L"assets\\player\\\sounds\\pain.wav"
#define POWERED_SOUND_FILE L"assets\\powerup\\\sounds\\pu.wav"

#define IDLE_SPEED 0.08f
#define RUN_SPEED 0.1f
#define DEATH_SPEED 0.5f
#define ATTACK_SPEED 0.05f
#define KNOCKOUT_SPEED 0.05f


#define KNOCKOUT_POWER 25.0f


#define W_Z_DAMAGE 100.0f
#define N_Z_DAMAGE 200.0f
#define H_Z_DAMAGE 300.0f


#define SHOOT_COOLDOWN 0.3f

Hero::Hero(Vector2D initPos, Vector2D vel, float scX, float scY, float rotation, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:
	PlayableCharacter::PlayableCharacter(initPos,vel, rotation, scX, scY, activated, paths)
{
	this->animLooped = true;
	this->animated = true;
	type = ObjectType::SHIP;
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
	//animPaths[L"IDLE"] = std::list<std::wstring>{L""};
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

Hero::~Hero()
{
	
}

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




void Hero::Updated(float timeFrame)
{

	ObjectManager::getInstance().getLevelManager()->SetXPos(this->position.XValue);
	if (this->active)
	{
		//Vector2D move(2.0f, 2.0f);
		float rotOff = 0.06f;

	
		//ObjectManager::getInstance().getLevelManager()->SetYPos(this->position.YValue);
		ObjectManager::getInstance().getLevelManager()->SetMaxHP(this->maxHealth);
		ObjectManager::getInstance().getLevelManager()->SetHP(this->health);

		if (this->posOffsetPower > 30.0f) {
			if (this->currentAnimation == RUN) {
				animTime = RUN_SPEED / 2;
			}
		}

		this->AnimUtilityUpdate(animTime, timeFrame);
	

		
		if (!knocked && this->shapeExist) {
			if (!attacking) {
				currentAnimation = IDLE;
				animTime = IDLE_SPEED;
			}
			if(ObjectManager::getInstance().getLevelManager()->getStartTimer()<=0.0f)
				this->control(timeFrame);
		}

		if(this->shootCoolDown>=0.0f)
			shootCoolDown -= timeFrame;

		if(knocked)
			playAnimOnce(FALL, timeFrame);
		if(attacking)
			playAnimOnce(ATTACK, timeFrame);


		if (this->invincTimer >= 0.0f) {
			this->alpha = 0.6f;
			this->invincTimer -= timeFrame;
		}
		else {
			this->alpha = 0.0f;
		}

		if (this->poweredUpTimer >= 0.0f) {
			this->poweredUpTimer -= timeFrame;
		}

		Vector2D friction = -(this->frictionPower) * this->velocity * timeFrame;
		this->velocity += friction;

		RestrictMovement(ObjectManager::getInstance().getLevelManager()->getMinY(),
						 ObjectManager::getInstance().getLevelManager()->getMinPlayerX(),
						 ObjectManager::getInstance().getLevelManager()->getMaxY(),
						 ObjectManager::getInstance().getLevelManager()->getMaxPlayerX(),
						 ObjectManager::getInstance().getLevelManager()->getMaxCameraX(),
						 ObjectManager::getInstance().getLevelManager()->getMinCameraX(),
						 true
						);

		this->position += this->velocity * timeFrame;
		
		if (this->shapeExist) {
			int width = 0;
			int height = 0;
			MyDrawEngine::GetInstance()->GetDimensions(this->image, height, width);
			this->boundingCircle.PlaceAt(this->position, this->scaleY * width / 2);

		}

		if (health <= 0) {
			if (this->currentAnimation != DEATH) {
				this->alpha = 0.5f;
				ObjectManager::getInstance().getLevelManager()->PlayerDead();
				ObjectManager::getInstance().Add(L"Dead Screen", { 0.0f , 0.0f }, { 0.0f, 0.0f }, 0.0f, 10.0f, 10.0f);
				currentAnimation = DEATH;
				this->shapeExist = false;
				this->animLooped = false;
				this->animTime = DEATH_SPEED;
				MySoundEngine::GetInstance()->Play(this->deathSound);
			}
		}
		
		
	}

}

void Hero::ProcessCollision(std::shared_ptr<CollidableObject> other)
{
	if (this->active) {
		if (other->DoesShapeExist()) {
			if (this->invincTimer<=0.0f) {

				if (other->GetType() == ObjectType::ZOMBIE_WEAK) {

					this->currentAnimation = FALL;
					this->knockBack(KNOCKOUT_POWER/2, KNOCKOUT_SPEED, other);
					invincTimer = knockedTimer * 3;
					this->health -= W_Z_DAMAGE;

					MySoundEngine::GetInstance()->Play(this->hurtSound);
				}
				if (other->GetType() == ObjectType::POWER_UP) {

					other->Deactivate();
					this->poweredUpTimer = POWEREDUP_TIMER;

					MySoundEngine::GetInstance()->Play(this->poweredSound);
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


			}
		}
	}

	
}

void Hero::control(float timeFrame, int up, int left, int down, int right, int run, int shoot)
{
	MyInputs::GetInstance()->SampleKeyboard();
	if (MyInputs::GetInstance()->KeyPressed(run))
	{
		this->posOffsetPower = 50.0f;
		
	}
	else {
		this->posOffsetPower = 30.0f;
	}
	if (MyInputs::GetInstance()->KeyPressed(up))
	{
		Vector2D acc;
		acc.setBearing(this->rotation, this->AccPower);
		this->velocity += acc * timeFrame * posOffsetPower;
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

	if (MyInputs::GetInstance()->NewKeyPressed(shoot)&&this->shapeExist&&this->shootCoolDown<=0.0f)
	{
		this->currentAnimation = ATTACK;
		this->attacking = true;
		this->animTime = ATTACK_SPEED;
		this->attackTimer = anims[currentAnimation].size() * animTime;

		float rotation = this->rotation;
		if (this->scaleX < 0) {
			rotation = this->rotation + 3.1415f;
		}
		MySoundEngine::GetInstance()->Play(this->fireSound);
		if (this->poweredUpTimer > 0.0f) {
			ObjectManager::getInstance().Add(L"Strong Bullet", this->position, this->velocity, rotation + 3.1415f / 2, this->scaleX * 2, -this->scaleY * 2);
		}
		else {
			ObjectManager::getInstance().Add(L"Bullet", this->position, this->velocity, rotation + 3.1415f / 2, this->scaleX * 2, -this->scaleY * 2);
		}
		this->shootCoolDown = SHOOT_COOLDOWN;
	}

	

}

