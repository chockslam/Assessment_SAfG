#include "Bullet.h"
#include "mydrawengine.h"

Bullet::Bullet(Vector2D initPos, Vector2D vel, float rotation, float sc, bool activated, std::wstring path)
	:
	GameObject::GameObject(initPos, rotation, sc, activated, path),
	velocity(vel)
{
}

void Bullet::Updated(float timeFrame)
{
	if (this->active) {
		this->velocity.setBearing(this->rotation, 500.0f);
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
		timer -= timeFrame;
		if (timer <= 0) {
			this->active = false;
		}
	}
	
}
