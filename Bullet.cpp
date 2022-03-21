#include "Bullet.h"
#include "mydrawengine.h"
#include "ObjectManager.h"


#define BULLET_COOLDOWN 0.1f
#define ROT_COMPENSATION 3.1415f/2

Bullet::Bullet(Vector2D initPos, Vector2D vel, float rotation, float sc, bool activated, std::list<std::wstring> paths)
	:
	CollidableObject::CollidableObject(initPos, rotation, sc, activated, L""),
	picturePaths(paths)
{
	type = ObjectType::BULLET;
}

void Bullet::Updated(float timeFrame)
{
	if (this->active) {


		if (it == pictures.end()) {
			this->active = false;
		}
		if (coolDownAnim <= 0) {
			image = *it;
			it++;
			coolDownAnim = BULLET_COOLDOWN;
		}
		coolDownAnim -= timeFrame;


		this->velocity.setBearing(this->rotation, 1000.0f);
		this->position += this->velocity * timeFrame;
		
		

		int width = 0;
		int height = 0;
		MyDrawEngine::GetInstance()->GetDimensions(this->image, height, width);
	
		this->boundingRect.PlaceAt(Vector2D(this->position.XValue - width/2 * this->scale, this->position.YValue - height / 2 * this->scale), Vector2D(this->position.XValue + width / 2 * this->scale, this->position.YValue + height / 2 * this->scale));
	}
	
}

void Bullet::Initialize()
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();

	for (auto path : picturePaths)
	{
		pictures.push_back(pDE->LoadPicture(path.c_str()));
	}
	it = pictures.begin();
	image = *it;
}

void Bullet::Render()
{
	if (this->active) {
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(this->position, this->image, this->scale, this->rotation-ROT_COMPENSATION);
	}
}

void Bullet::ProcessCollision(std::shared_ptr<CollidableObject> other)
{
	if (other->GetType() == ObjectType::ASTEROID) {
		if (this->active)
			this->Deactivate();
		ObjectManager::getInstance().Add(L"Puff", this->position, Vector2D(), this->rotation, this->scale/2.0f);
	}
}


IShape2D& Bullet::GetShape()
{
	// TODO: insert return statement here
	return this->boundingRect;
}
