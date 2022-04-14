/*
	* Healthbar .cpp file
	* 19012503
	* Aim of the class:		Reprsents health bar located on the top of the screen.
	* Notes: Quite strongly coupled to LevelManager.
*/


#include "HealthBar.h"
#include "ObjectManager.h"
#include "mydrawengine.h"

HealthBar::HealthBar(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:
	UIElement::UIElement(initPos, rotation, scX, scY, activated, paths),
	initScaleX(scX)
{
}

void HealthBar::Updated(float timeFrame)
{
	// calculate ScaleX based on the current health proporition to max health.
	// initScaleX - initial scale x.
	this->maxHealth = ObjectManager::getInstance().getLevelManager()->getMaxHeroHealth();
	this->currHealth = ObjectManager::getInstance().getLevelManager()->getHeroHealth();
	this->scaleX = (this->currHealth>0.0f) ? this->initScaleX * this->currHealth / this->maxHealth : 0.0f;

}
