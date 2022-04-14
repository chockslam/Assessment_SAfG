/*
	* UIElement .cpp file
	* 19012503
	* Aim of the class: Represents any UI Element.
	*                   It has a specific Render function that allows rendering 'on the camera screen'. (functions implementation)
*/


#include "UIElement.h"
#include "mydrawengine.h"
UIElement::UIElement(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:
	GameObject::GameObject({0,0}, rotation, scX, scY, activated, paths),
	localPosition(initPos)
{
	this->animLooped = true;
}

/// <summary>
/// Specific to UIElement render function.
/// </summary>
void UIElement::Render()
{
	// restrict position to 'camera's lense'
	this->position = MyDrawEngine::GetInstance()->theCamera.getWorldPosition() + this->localPosition;
	// render as usual.
	GameObject::Render();
}
