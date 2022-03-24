#include "GameObject.h"
#include "ErrorLogger.h"
#include "mydrawengine.h"


GameObject::GameObject(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:
	position(initPos),
	rotation(rotation),
	active(activated),
	path(path),
	scaleX(scX),
	scaleY(scY),
	posOffsetPower(0.0f),
	coolDownAnim(-1.0f),
	animated(false),
	animPaths(paths),
	animLooped(false),
	animTime(0.0f)
{

	currentAnimation = L"IDLE";
	previousAnimation = L"IDLE";
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
	this->LoadPicture();
}

void GameObject::Render()
{
	if (this->active) {
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(this->position, this->image, this->scaleX, this->scaleY, this->rotation);
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

void GameObject::LoadPicture()
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();

	for (auto anim : animPaths)
	{
		if (anims.find(anim.first) == anims.end()) {
			std::list<int> animationFrames;
			for (auto pic : anim.second) {
				auto frame = pDE->LoadPicture(pic.c_str());
				animationFrames.push_back(frame);
			}
			anims.emplace(anim.first, animationFrames);
		}
	}
	it = anims[currentAnimation].begin();
	image = *it;
}

void GameObject::AnimUtilityUpdate(float animSpeed, float timeFrame)
{
	if (this->animated)
	{
		if (previousAnimation != currentAnimation) {
			it = anims[currentAnimation].begin();
		}
		if (it == anims[currentAnimation].end()) {
			if (this->animLooped) {
				this->it = anims[currentAnimation].begin();
			}
			else {
				this->active = false;
			}
		}
		if (coolDownAnim <= 0) {
			image = *it;
			it++;
			coolDownAnim = animSpeed;
		}
		coolDownAnim -= timeFrame;
	}
	previousAnimation = currentAnimation;
}


