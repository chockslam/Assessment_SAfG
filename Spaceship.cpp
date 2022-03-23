#include "Spaceship.h"


#include "mydrawengine.h"
#include "myinputs.h"
#include "mysoundengine.h"
#include "LevelManager.h"


#include "ObjectManager.h"

// #include "Bullet.h"


#define PATH L"assets\\ship.bmp"

#define IDLE_SPEED 0.1f
#define KNOCKOUT_TIMER 2.0f

Spaceship::Spaceship(Vector2D initPos, Vector2D vel, float scX, float scY, float rotation, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:
	CollidableObject::CollidableObject(initPos, rotation, scX, scY, activated, paths),
	velocity(vel)
{
	this->animLooped = true;
	this->animated = true;
	type = ObjectType::SHIP;
	image = 0;
}

Spaceship::Spaceship(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, bool activated)
	:
	Spaceship::Spaceship(initPos, vel, scX, scY, rotation, activated, std::unordered_map<std::wstring, std::list<std::wstring>>())
{
	animPaths[L"IDLE"] = std::list<std::wstring>{L""};
}

Spaceship::Spaceship(Vector2D initPos, Vector2D vel, float rotation)
	:
	Spaceship::Spaceship(initPos, vel, rotation, 5.0f,5.0f, false)
{
}

Spaceship::Spaceship(Vector2D initPos, Vector2D vel, bool activated)
	:
	Spaceship::Spaceship(initPos,vel,0.0f,5.0f,5.0f,activated)
{
}

Spaceship::Spaceship(Vector2D initPos, Vector2D vel)
	:
	Spaceship::Spaceship(initPos,vel, false)
{

}

Spaceship::Spaceship(Vector2D initPos)
	:
	Spaceship::Spaceship(initPos,Vector2D(1,0))
{
}

IShape2D& Spaceship::GetShape()
{
	return this->boundingCircle;
}

Spaceship::Spaceship()
	:
	Spaceship::Spaceship(Vector2D(0, 0))
{
}

Spaceship::~Spaceship()
{
	
}




void Spaceship::Updated(float timeFrame)
{

	if (this->active)
	{
		//Vector2D move(2.0f, 2.0f);
		float rotOff = 0.06f;
		MyInputs* pInputs = MyInputs::GetInstance();
		pInputs->SampleKeyboard();

		//if (currentAnimation == L"FALL") {
		//	if (it == anims[L"FALL"].end()) {
		//		currentAnimation = L"IDLE";
		//		it = anims[L"IDLE"].begin();
		//	}
		//}


		this->AnimUtilityUpdate(IDLE_SPEED, timeFrame);
		//pos += move;
		//rot += rotOff;
		

		//Acceleration
		if (!knocked) {
			
		}
		
		if (!knocked) {

			if (pInputs->KeyPressed(DIK_LSHIFT))
			{
				this->posOffsetPower = 50.0f;
				currentAnimation = L"RUN";
			}
			else {
				this->posOffsetPower = 5.0f;
				currentAnimation = L"IDLE";
			}

			if (pInputs->KeyPressed(DIK_W))
			{
				Vector2D acc;
				acc.setBearing(this->rotation, this->AccPower);
				this->velocity += acc * timeFrame * posOffsetPower;

			}
			if (pInputs->KeyPressed(DIK_S))
			{

				Vector2D acc;
				acc.setBearing(this->rotation + 3.1415f, this->AccPower);
				this->velocity += acc * timeFrame * posOffsetPower;

			}
			if (pInputs->KeyPressed(DIK_D))
			{

				if (this->scaleX < 0)
					this->scaleX = -this->scaleX;
				Vector2D acc;
				acc.setBearing(this->rotation + 3.1415f / 2, this->AccPower);
				this->velocity += acc * timeFrame * posOffsetPower;

			}
			if (pInputs->KeyPressed(DIK_A))
			{

				if (this->scaleX >= 0)
					this->scaleX = -this->scaleX;
				Vector2D acc;
				acc.setBearing(this->rotation - 3.1415f / 2, this->AccPower);
				this->velocity += acc * timeFrame * posOffsetPower;

			}

			if (pInputs->NewKeyPressed(DIK_SPACE))
			{
				float rotation = this->rotation;
				if (this->scaleX < 0) {
					rotation = this->rotation + 3.1415f;
				}
				ObjectManager::getInstance().Add(L"Bullet", this->position, this->velocity, rotation + 3.1415f / 2, this->scaleX * 2, -this->scaleY * 2, 1);
			}
		}
		else {
			knockedTimer -= timeFrame;
			if (knockedTimer <= 0) {
				knocked = false;
				knockedTimer = anims[L"FALL"].size()*IDLE_SPEED;
			}
		}

		Vector2D friction = -(this->frictionPower) * this->velocity * timeFrame;
		this->velocity += friction;
		this->position += this->velocity * timeFrame;
		
		

		int width = 0;
		int height = 0;
		MyDrawEngine::GetInstance()->GetDimensions(this->image, height, width);
		this->boundingCircle.PlaceAt(this->position, this->scaleY * width / 2);
		MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(position.XValue + 500.0f, -position.YValue));

	}
	
/*
	//Sounds

	if (pInputs->NewKeyPressed(DIK_SPACE))
	{
		pSE->Play(shootSound);
	}
	if (pInputs->NewKeyPressed(DIK_W))
	{
		pSE->Play(thrustSound, true);
		thrustOn = true;
	}
	else if (!pInputs->KeyPressed(DIK_W) && thrustOn) {
		pSE->Stop(thrustSound);
		thrustOn = false;
	}
*/
	// this->boundingRect.PlaceAt(this->position.YValue+ 5 * this->scale, this->position.XValue - 5 * this->scale, this->position.YValue - 5 * this->scale, this->position.XValue + 5 * this->scale);

}

void Spaceship::ProcessCollision(std::shared_ptr<CollidableObject> other)
{

	if(other->GetType() == ObjectType::ZOMBIE_WEAK) {
		if (this->active) {
			currentAnimation = L"FALL";
			Vector2D acc;
			float direction = -3.1415f / 2;
			if (this->scaleX < 0)
				direction = -direction;
			acc.setBearing(this->rotation + direction, this->AccPower);
			this->velocity += acc  *  posOffsetPower;
			knocked = true;
		}

	}
}

//void Spaceship::Render()
//{
//	
//}
