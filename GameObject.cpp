#include "GameObject.h"
#include "ErrorLogger.h"
#include "mydrawengine.h"



GameObject::GameObject(Vector2D initPos, float rotation, float sc, bool activated, std::wstring path)
	:
	position(initPos),
	rotation(rotation),
	active(activated),
	path(path),
	scale(sc),
	posOffsetPower(0.0f)
{
}


GameObject::~GameObject()
{
}

bool GameObject::IsActive() const
{
	return this->active;
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
}

void GameObject::Render()
{
	if (this->active) {
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(this->position, this->image, this->scale, this->rotation);
	}
}

void GameObject::wrap()
{
	if (this->position.XValue > MyDrawEngine::GetInstance()->GetScreenWidth()) {
		this->position.XValue = -MyDrawEngine::GetInstance()->GetScreenWidth();
	}
	if (this->position.XValue < -MyDrawEngine::GetInstance()->GetScreenWidth()) {
		this->position.XValue = MyDrawEngine::GetInstance()->GetScreenWidth();
	}
	if (this->position.YValue > MyDrawEngine::GetInstance()->GetScreenHeight()) {
		this->position.YValue = -MyDrawEngine::GetInstance()->GetScreenHeight();
	}
	if (this->position.YValue < -MyDrawEngine::GetInstance()->GetScreenHeight()) {
		this->position.YValue = MyDrawEngine::GetInstance()->GetScreenHeight();
	}
}


