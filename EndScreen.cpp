#include "EndScreen.h"
#include "ObjectManager.h"
EndScreen::EndScreen(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:UIElement::UIElement(initPos, rotation, scX, scY, activated, paths)
{
}

void EndScreen::Updated(float timeFrame)
{
	if (this->duration <= 0.0f) {
		this->active = false;
	}
	this->duration -= timeFrame;

}



void EndScreen::Initialize()
{
	GameObject::Initialize();
	this->duration = ObjectManager::getInstance().getLevelManager()->getEndTimer() / 60;
}
