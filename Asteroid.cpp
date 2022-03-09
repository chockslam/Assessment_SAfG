#include "Asteroid.h"
#include "mydrawengine.h"
#include <random>

Asteroid::Asteroid(Vector2D initPos, Vector2D vel, float rotation, float sc, bool activated, std::wstring path)
	:
	GameObject::GameObject(initPos, rotation, sc, activated, path),
	velocity(vel)
{
}

void Asteroid::Updated(float timeFrame)
{
	this->velocity.setBearing(this->rotation, 200.0f);
	this->position += this->velocity * timeFrame;
	// Wrap around
	if (this->position.XValue > MyDrawEngine::GetInstance()->GetScreenWidth()) {
		this->position.XValue = -MyDrawEngine::GetInstance()->GetScreenWidth();
	}
	if (this->position.XValue < -MyDrawEngine::GetInstance()->GetScreenWidth()) {
		this->position.XValue = MyDrawEngine::GetInstance()->GetScreenWidth();
	}
	if (this->position.YValue > MyDrawEngine::GetInstance()->GetScreenHeight()) {
		this->position.YValue = -MyDrawEngine::GetInstance()->GetScreenHeight();
	}
	if (this->position.YValue < -MyDrawEngine::GetInstance()->GetScreenHeight()) {
		this->position.YValue = MyDrawEngine::GetInstance()->GetScreenHeight();
	}
}
