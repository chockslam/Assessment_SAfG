/*
	* Start Screen .cpp file
	* 19012503
	* Aim of the class: Represents any screen displayed before the level starts (functions implementation).
	* DRAWBACK: Dead screen/End Screen/Start screen might be merged to reduce amount of code.
	* SIMILAR TO OTHER SCREENS IMPLEMENTATION - CHECK THEM FOR EXPLANATION.
*/

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
	//this->duration = ObjectManager::getInstance().getLevelManager()->getStartTimer();
	this->duration -= timeFrame;
}



void StartScreen::Initialize()
{
	GameObject::Initialize();
	this->duration = ObjectManager::getInstance().getLevelManager()->getStartTimer();
}
