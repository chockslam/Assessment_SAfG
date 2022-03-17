#include "Asteroid.h"
#include "mydrawengine.h"
#include <random>

Asteroid::Asteroid(Vector2D initPos, Vector2D vel, float rotation, float sc, bool activated, std::wstring path)
	:
	GameObject::GameObject(initPos, rotation, sc, activated, path),
	velocity(vel)
{
	type = ObjectType::ASTEROID;
	this->collidable = true;
}

void Asteroid::Updated(float timeFrame)
{
	if (this->active)
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
		int width = 0;
		int height = 0;
		MyDrawEngine::GetInstance()->GetDimensions(this->image,height,width);
		this->boundingCircle.PlaceAt(this->position, this->scale * width / 2);
	}
	
	
}

IShape2D& Asteroid::GetShape()
{
	// TODO: insert return statement here
	return this->boundingCircle;
}

void Asteroid::ProcessCollision(std::shared_ptr<GameObject> other)
{
	if (other->GetType() == ObjectType::BULLET) {
		OutputDebugString(L"Asteroid collided with bullet \n");
		if (this->active)
			this->Deactivate();
	}
}
