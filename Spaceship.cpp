#include "Spaceship.h"


#include "mydrawengine.h"
#include "myinputs.h"
#include "mysoundengine.h"


#define PATH L"assets\\ship.bmp"


Spaceship::Spaceship(Vector2D initPos, Vector2D vel, float rotation, bool activated, std::wstring path)
	:
	GameObject::GameObject(initPos, rotation, activated, path),
	velocity(vel)
{
	image = 0;
	posOffset = 1.0f;
	rotOffset = 0.07f;
}

Spaceship::Spaceship(Vector2D initPos, Vector2D vel, float rotation, bool activated)
	:
	Spaceship::Spaceship(initPos,vel,rotation,activated,PATH)
{
}

Spaceship::Spaceship(Vector2D initPos, Vector2D vel, float rotation)
	:
	Spaceship::Spaceship(initPos, vel, rotation, false)
{
}

Spaceship::Spaceship(Vector2D initPos, Vector2D vel, bool activated)
	:
	Spaceship::Spaceship(initPos,vel,0.0f,activated)
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

Spaceship::Spaceship()
	:
	Spaceship::Spaceship(Vector2D(0, 0))
{
}

//void Spaceship::Initialize()
//{
//
//	
//}

void Spaceship::Updated()
{


	//Vector2D move(2.0f, 2.0f);
	float rotOff = 0.06f;
	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();
	MySoundEngine* pSE = MySoundEngine::GetInstance();


	//pos += move;
	//rot += rotOff;
	
	//Acceleration
	if (pInputs->KeyPressed(DIK_LSHIFT))
	{
		this->posOffsetPower = 2.0f;
	}
	else {
		this->posOffsetPower = 1.0f;
	}


	//Movements
	if (pInputs->KeyPressed(DIK_W))
	{

		Vector2D velocity;

		velocity += this->up;
		velocity.setBearing(this->rotation, 4.0f);
		this->position += velocity * posOffsetPower;
	}
	if (pInputs->KeyPressed(DIK_S))
	{
		this->velocity = this->down;
		this->velocity.setBearing(this->rotation, -4.0f);
		this->position += this->velocity * posOffsetPower;
	}
	
	//Rotation
	if (pInputs->KeyPressed(DIK_LEFT))
	{
		this->rotation -= this->rotOffset;
	}
	if (pInputs->KeyPressed(DIK_RIGHT))
	{
		this->rotation += this->rotOffset;
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

	this->Render();
}

//void Spaceship::Render()
//{
//	
//}
