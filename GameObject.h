/*
	* Game Object .h file
	* 19012503
	* Aim of the class:		Represents any game object in the game, i.e. bullet, ui elements, collidable objects....
							Abstract class.
*/

#pragma once
#include "vector2D.h"
#include "Shapes.h"
#include <string>
#include <memory>
#include <list>
#include <unordered_map>
#include "TypeGO.h"

class GameObject
{
public:
	GameObject(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);
	virtual ~GameObject();
	bool IsActive() const;
	void Activate();
	void Deactivate();
	virtual void Initialize();
	virtual void Updated(float timeFrame) = 0;
	virtual void Render();
	// returns position of the game object.
	Vector2D getPos() const { return this->position; };
	// returns type of the object.
	const ObjectType GetType() const { return this->type; };
	// empty process proximity function. used for zombies and a hero.
	virtual void ProcessProximity(std::shared_ptr<GameObject> other) {};

protected:
	void LoadAnimations();
	void AnimUtilityUpdate(float animSpeed, float timeFrame);

	// default object type.
	ObjectType type = ObjectType::UNKNOWN;


	float animTime;															// animation utility variable - denotes the speed of the animation and is MEANT to be passed to animUtilityUpdate function.
	bool animLooped;														// Whether the anim is looped. If it is not looped, the object is set to inactive after the first itteration. 
	bool animated;															// Whether the gameObject is animated.
	float coolDownAnim;														// animation utility variable - used inside AnimUtilityUpdate function.
	std::wstring currentAnimation;											// name of the current animation
	std::wstring previousAnimation;											// name of the previous animation (in the previous frame)
	std::unordered_map<std::wstring, std::list<std::wstring>> animPaths;	// animation utility variable (set in the constructor - passed by the programmer) - reflects collection of animation (paths) in the gameObject. 
	std::unordered_map<std::wstring, std::list<int>> anims;					// animation utility variable (loaded animations - mysoundengine specific implementation) - reflects collection of animation (integers) in the gameObject - used in the AnimUtilityUpdate.
	std::list<int>::iterator it;											// animation utility variable - iterator used to traverse through the list of current animation in animUtilityUpdate function.

	// Horizontal (x) and Vertical (y) scale.
	float scaleX;													
	float scaleY;

	// facilitate visibility of the object.
	float alpha;

	Vector2D position;
	float rotation;
	
	// currently rendered image
	int image;

	// is object active?
	bool active;
};

