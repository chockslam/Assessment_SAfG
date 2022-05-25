/*
	* Game Object .cpp file
	* 19012503
	* Aim of the class:		Represents any game object in the game, i.e. bullet, ui elements, collidable objects.... (functions implementations)
							Abstract class.
*/

#include "GameObject.h"
#include "ErrorLogger.h"
#include "mydrawengine.h"

#include "AnimMasks.h"
/// <summary>
/// Constructor.
/// </summary>
GameObject::GameObject(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:
	position(initPos),
	rotation(rotation),
	active(activated),
	scaleX(scX),
	scaleY(scY),
	coolDownAnim(-1.0f),
	animated(false),
	animPaths(paths),
	animLooped(false),
	animTime(0.0f),
	alpha(0.0f)
{
	// IDLE - default animation.
	currentAnimation = IDLE;
	previousAnimation = IDLE;
}


GameObject::~GameObject()
{
}

/// <summary>
/// Whether the object is active.
/// </summary>
bool GameObject::IsActive() const
{
	return this->active;
}

/// <summary>
/// Add animation
/// </summary>
/// <param name="state"> type of animation </param>
/// <param name="listOfAnims">actual pictures</param>
void GameObject::SetAnimation(std::wstring state, std::list<std::wstring> listOfAnims)
{
	// empty list of integers/PictureIndices 
	std::list<int> animationFrames;
	// for every path in the list.
	for (auto pic : listOfAnims) {
		// load picture and push it to the list.
		auto frame = MyDrawEngine::GetInstance()->LoadPicture(pic.c_str());
		animationFrames.push_back(frame);
	}
	// emplace name and list of animation to the map.
	anims.emplace(state, animationFrames);
}


/// <summary>
/// Activate object.
/// </summary>
void GameObject::Activate()
{
	if (!active) {
		active = true;
	}
	else {
		ErrorLogger::Writeln(L"The object is already activated");
	}
}

/// <summary>
/// Deactivate the object.
/// </summary>
void GameObject::Deactivate()
{
	if (active) {
		active = false;
	}
	else {
		ErrorLogger::Writeln(L"The object is already deativated");
	}
}

/// <summary>
/// Initialize functions. Loads all the animations.
/// </summary>
void GameObject::Initialize()
{
	this->LoadAnimations();
}

/// <summary>
/// Render function.
/// </summary>
void GameObject::Render()
{
	if (this->active) {
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(this->position, this->image, this->scaleX, this->scaleY, this->rotation, this->alpha);
	}
}


/// <summary>
/// Load animations into the map that is used in AnimUtilityUpdate(...) function.
/// </summary>
void GameObject::LoadAnimations()
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	
	// for every list...
	for (auto anim : animPaths)
	{
		// if anim is not found in the map, then process inserting loaded animations.
		if (anims.find(anim.first) == anims.end()) {
			// empty list of integers/PictureIndices 
			std::list<int> animationFrames;
			// for every path in the list.
			for (auto pic : anim.second) {
				// load picture and push it to the list.
				auto frame = pDE->LoadPicture(pic.c_str());
				animationFrames.push_back(frame);
			}
			// emplace name and list of animation to the map.
			anims.emplace(anim.first, animationFrames);
		}
	}
	// set itrator to the begin of IDLE animation (or any other default animation) list.
	it = anims[currentAnimation].begin();
	// rendered image is the first entry to the IDLE animation list.
	image = *it;
}

/// <summary>
/// Animation utility update function - should be called in the update function to handle animation.
/// Supports looped and once played animations.
/// If animationLooped == false. After playing the animation - object deactivated.
/// </summary>
/// <param name="animSpeed">How fast animation goes. The smaller number the slower. Recommend choose between 0.001f and 1.5f </param>
/// <param name="timeFrame">.. self explanatory ..</param>
void GameObject::AnimUtilityUpdate(float animSpeed, float timeFrame)
{
	
	// only process if the object is set to be animated.
	if (this->animated)
	{
		// if animation/state was changed start animation over. 
		if (previousAnimation != currentAnimation) {
			it = anims[currentAnimation].begin();
		}
		// if iterator reached end of the list
		if (it == anims[currentAnimation].end()) {
			
			// if animation is looped - start playing it over.
			// else deactivate the object.
			if (this->animLooped) {
				this->it = anims[currentAnimation].begin();
			}
			else {
				this->active = false;
			}
		}
		// Handle duration of each frame.
		// if coolDownAnim reaches 0.. then go to the next image and reset coolDownAnim with animSpeed.
		if (coolDownAnim <= 0.0f && this->active) {
			image = *it;							// dereference iterator.
			it++;									// increment iterator.
			coolDownAnim = animSpeed;				// reset animFrame duration.
		}
		coolDownAnim -= timeFrame;					// deduct timeFrame every frame.... 
	}
	previousAnimation = currentAnimation;			// every frame set previous animation to current animation. 
}


