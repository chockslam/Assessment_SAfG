#include "Asteroid.h"
#include "mydrawengine.h"
#include <random>

Asteroid::Asteroid(Vector2D initPos, Vector2D vel, float rotation, float sc, bool activated, std::wstring path)
	:
	CollidableObject::CollidableObject(initPos, rotation, sc, activated, path),
	velocity(vel)
{
	type = ObjectType::ASTEROID;
}

void Asteroid::Updated(float timeFrame)
{
	if (this->active)
	{
		this->velocity.setBearing(this->rotation, 200.0f);
		this->position += this->velocity * timeFrame;
		
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

void Asteroid::ProcessCollision(std::shared_ptr<CollidableObject> other)
{
	if (other->GetType() == ObjectType::BULLET) {
		OutputDebugString(L"Asteroid collided with bullet \n");
		if (this->active)
			this->Deactivate();
	}
}
