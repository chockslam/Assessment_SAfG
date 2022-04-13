/*
	* End Screen .cpp file
	* 19012503
	* Aim of the class: Represents any screen displayed after the level is completed (functions implementation).

*/

#include "EndScreen.h"
#include "ObjectManager.h"
EndScreen::EndScreen(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:UIElement::UIElement(initPos, rotation, scX, scY, activated, paths)
{
}

/// <summary>
/// Update function.
/// </summary>
void EndScreen::Updated(float timeFrame)
{
	if (this->duration <= 0.0f) {
		this->active = false;
	}
	// Needs to be synchronised with level manager variable due to the occasional fps issues 
	// which might cause unpredicted behivior of the screen,
	// i.e. it stays for too short because time frame is too big.
	this->duration = ObjectManager::getInstance().getLevelManager()->getEndTimer();

}

/// <summary>
/// Initialize function.
/// </summary>
void EndScreen::Initialize()
{
	GameObject::Initialize();
	this->duration = ObjectManager::getInstance().getLevelManager()->getEndTimer();
}
