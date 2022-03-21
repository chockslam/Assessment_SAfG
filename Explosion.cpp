#include "Explosion.h"
#include "mydrawengine.h"

#define COOLDOWN 0.1f

Explosion::Explosion(Vector2D initPos, float rotation, float sc, bool activated, std::list<std::wstring> paths)
	:	
	GameObject::GameObject(initPos, rotation, sc, activated, L""),
	picturePaths(paths),
	coolDownAnim(COOLDOWN)
{
}

void Explosion::Updated(float timeFrame)
{
	if (this->active) {
		if (it == pictures.end()) {
			this->active = false;
		}
		if (coolDownAnim <= 0) {
			image = *it;
			it++;
			coolDownAnim = COOLDOWN;
		}
		coolDownAnim -= timeFrame;
	}

}


void Explosion::Initialize()
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	
	for (auto path : picturePaths) 
	{
		pictures.push_back(pDE->LoadPicture(path.c_str()));
	}
	it = pictures.begin();
	image = *it;
	
}

