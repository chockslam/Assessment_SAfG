/*
	* Dead Screen .cpp file
	* 19012503
	* Aim of the class: Represents any screen displayed after the player dies (functions implementation).
*/

#include "DeadScreen.h"
#include "ObjectManager.h"
#include "mydrawengine.h"

DeadScreen::DeadScreen(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:UIElement::UIElement(initPos, rotation, scX, scY, activated, paths)
{
}

/// <summary>
/// Update function.
/// </summary>
void DeadScreen::Updated(float timeFrame)
{
	if (this->duration<=0.0f) {
		this->active = false;
	}
	this->duration -= timeFrame;
}


/// <summary>
/// Initialize function.
/// </summary>
void DeadScreen::Initialize()
{
	GameObject::Initialize();
	this->duration = ObjectManager::getInstance().getLevelManager()->getDeathCoolDown();
}
/// <summary>
/// Rendering function.
/// </summary>
void DeadScreen::Render()
{
	UIElement::Render();
	// Write a string beneath the UI image.
	MyDrawEngine::GetInstance()->WriteText(this->position + Vector2D(-120, -700), L"YOU ARE DEAD", MyDrawEngine::RED, 0);
}
