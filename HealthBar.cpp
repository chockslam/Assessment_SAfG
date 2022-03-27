#include "HealthBar.h"
#include "LevelManager.h"
#include "mydrawengine.h"

HealthBar::HealthBar(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:
	UIElement::UIElement(initPos, rotation, scX, scY, activated, paths),
	initScaleX(scX)
{
}

void HealthBar::Updated(float timeFrame)
{
	UIElement::Updated(timeFrame);
	this->maxHealth = LevelManager::getInstance()->getMaxHeroHealth();
	this->currHealth = LevelManager::getInstance()->getHeroHealth();
	this->scaleX = this->initScaleX * this->currHealth / this->maxHealth;

}
