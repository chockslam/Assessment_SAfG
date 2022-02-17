#include "Spaceship.h"


#include "mydrawengine.h"
#define PATH L"assets\\ship.bmp"


Spaceship::Spaceship(Vector2D initPos, Vector2D vel, float rotation, bool activated, std::wstring path)
	:
	GameObject::GameObject(initPos, rotation, activated),
	velocity(vel),
	path(path)
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

void Spaceship::Initialize()
{

	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	image = pDE->LoadPicture(path.c_str());
	printf("");
}

void Spaceship::Updated()
{
	this->Render();
}

void Spaceship::Render()
{
	if (this->active) {
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(this->position, image, 5.0f, this->rotation);
	}
}
