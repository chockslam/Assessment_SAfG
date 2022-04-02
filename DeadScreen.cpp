#include "DeadScreen.h"
#include "ObjectManager.h"
#include "mydrawengine.h"

DeadScreen::DeadScreen(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:UIElement::UIElement(initPos, rotation, scX, scY, activated, paths)
{
}

void DeadScreen::Updated(float timeFrame)
{
	if (this->duration<=0.0f) {
		this->active = false;
	}
	this->duration = ObjectManager::getInstance().getLevelManager()->getDeathCoolDown();

}



void DeadScreen::Initialize()
{
	GameObject::Initialize();
	this->duration = ObjectManager::getInstance().getLevelManager()->getDeathCoolDown();
}

void DeadScreen::Render()
{

	UIElement::Render();
	MyDrawEngine::GetInstance()->WriteText(this->position + Vector2D(-120, -700), L"YOU ARE DEAD", MyDrawEngine::RED, 0);
}
