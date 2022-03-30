#include "UIElement.h"
#include "mydrawengine.h"
UIElement::UIElement(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:
	GameObject::GameObject({0,0}, rotation, scX, scY, activated, paths),
	localPosition(initPos)
{
	this->animLooped = true;
}


void UIElement::Render()
{
	this->position = MyDrawEngine::GetInstance()->theCamera.getWorldPosition() + this->localPosition;
	GameObject::Render();
}
