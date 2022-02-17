#include "Spaceship.h"

MyDrawEngine* pDE = MyDrawEngine::GetInstance();

#define PATH L"assets\\ship.bmp"


Spaceship::Spaceship(Vector2D initPos, Vector2D vel, float rotation, bool activated)
	:
	GameObject::GameObject(initPos, rotation,activated),
	velocity(vel)
{
	image = -1;
	posOffset = 1.0f;
	rotOffset = 0.07f;
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

void Spaceship::Initialize()
{
	image = pDE->LoadPicture(path);
	printf("");
}

void Spaceship::Updated()
{
	this->Render();
}

void Spaceship::Render()
{
	if(this->active)
		pDE->DrawAt(this->position, image, 5.0f, this->rotation);
}
