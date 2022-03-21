#include "Spaceship.h"


#include "mydrawengine.h"
#include "myinputs.h"
#include "mysoundengine.h"
#include "LevelManager.h"

// #include "Bullet.h"


#define PATH L"assets\\ship.bmp"



Spaceship::Spaceship(Vector2D initPos, Vector2D vel, float sc, float rotation, bool activated, std::wstring path)
	:
	CollidableObject::CollidableObject(initPos, rotation, sc, activated, path),
	velocity(vel)
{
	type = ObjectType::SHIP;
	this->om = nullptr;
	image = 0;
}

Spaceship::Spaceship(Vector2D initPos, Vector2D vel, float rotation, float sc, bool activated)
	:
	Spaceship::Spaceship(initPos,vel, sc,rotation,activated,PATH)
{
}

Spaceship::Spaceship(Vector2D initPos, Vector2D vel, float rotation)
	:
	Spaceship::Spaceship(initPos, vel, rotation, 5.0f, false)
{
}

Spaceship::Spaceship(Vector2D initPos, Vector2D vel, bool activated)
	:
	Spaceship::Spaceship(initPos,vel,0.0f,5.0f,activated)
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


void Spaceship::Initialize(std::shared_ptr<ObjectManager> om)
{
	GameObject::Initialize();
	
	this->om = om;

}


void Spaceship::Updated(float timeFrame)
{

	if (this->active)
	{
		//Vector2D move(2.0f, 2.0f);
		float rotOff = 0.06f;
		MyInputs* pInputs = MyInputs::GetInstance();
		pInputs->SampleKeyboard();


		//pos += move;
		//rot += rotOff;

		//Acceleration
		if (pInputs->KeyPressed(DIK_LSHIFT))
		{
			this->posOffsetPower = 50.0f;
		}
		else {
			this->posOffsetPower = 5.0f;
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
			acc.setBearing(this->rotation, (-this->AccPower));
			this->velocity += acc * timeFrame * posOffsetPower;

		}

		if (pInputs->NewKeyPressed(DIK_SPACE))
		{
			if (this->om)
				om->Add(L"Bullet", this->position, this->velocity, this->rotation, 10.0f, 1, this->om);
		}

		Vector2D friction = -(this->frictionPower) * this->velocity * timeFrame;
		//this->velocity += friction + this->down;
		this->velocity += friction;
		this->position += this->velocity * timeFrame;

		// Wrap around
		
		//Rotation
		if (pInputs->KeyPressed(DIK_LEFT))
		{
			this->rotation -= this->rotOffset * timeFrame;
		}
		if (pInputs->KeyPressed(DIK_RIGHT))
		{
			this->rotation += this->rotOffset * timeFrame;
		}

		int width = 0;
		int height = 0;
		MyDrawEngine::GetInstance()->GetDimensions(this->image, height, width);
		this->boundingCircle.PlaceAt(this->position, this->scale * width / 2);
		MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(position.XValue + 500.0f, -position.YValue));

	}
	else {
		om = nullptr;
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

	if(other->GetType() == ObjectType::ASTEROID) {
		if (this->active) {
			this->Deactivate();
			if (this->om)
				this->om->Add(L"Explosion", this->position, Vector2D(), this->rotation, this->scale, 1);

			LevelManager::getInstance()->PlayerDead();

		}

	}
}

//void Spaceship::Render()
//{
//	
//}
