#include "StartScreen.h"
#include "ObjectManager.h"

StartScreen::StartScreen(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:UIElement::UIElement(initPos, rotation, scX, scY, activated, paths)
{
}

void StartScreen::Updated(float timeFrame)
{
	if (this->duration <= 0.0f) {
		this->active = false;
	}
	this->duration = ObjectManager::getInstance().getLevelManager()->getStartTimer();

}



void StartScreen::Initialize()
{
	GameObject::Initialize();
	this->duration = ObjectManager::getInstance().getLevelManager()->getStartTimer();
}
