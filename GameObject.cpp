#include "GameObject.h"
#include "ErrorLogger.h"
#include "mydrawengine.h"



GameObject::GameObject(Vector2D initPos, float rotation, bool activated, std::wstring path)
	:
	position(initPos),
	rotation(rotation),
	active(activated),
	path(path)
{
}


GameObject::~GameObject()
{
}

void GameObject::Activate()
{
	if (!active) {
		active = true;
	}
	else {
		ErrorLogger::Writeln(L"The object is already activated");
	}
}

void GameObject::Deactivate()
{
	if (active) {
		active = false;
	}
	else {
		ErrorLogger::Writeln(L"The object is already deativated");
	}
}

void GameObject::Initialize()
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	image = pDE->LoadPicture(path.c_str());
	printf("");
}

void GameObject::Updated()
{
}

void GameObject::Render()
{
	if (this->active) {
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(this->position, this->image, 5.0f, this->rotation);
	}
}

