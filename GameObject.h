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
	Vector2D getPos() const { return this->position; };
	void wrap();
	const ObjectType GetType() const { return this->type; };
	virtual void ProcessProximity(std::shared_ptr<GameObject> other) {};

protected:
	void LoadPicture();
	void AnimUtilityUpdate(float animSpeed, float timeFrame);


	ObjectType type = ObjectType::UNKNOWN;

	bool animLooped;
	bool animated;
	float coolDownAnim;
	std::wstring currentAnimation;
	std::wstring previousAnimation;

	std::unordered_map<std::wstring, std::list<std::wstring>> animPaths;
	//std::list<std::wstring> picturePaths;


	std::unordered_map<std::wstring, std::list<int>> anims;
	//std::list<int> pictures;
	
	std::list<int>::iterator it;

	float scaleX;
	float scaleY;

	Vector2D position;
	float posOffsetPower;
	
	float rotation;
	const float rotOffset = 1.0f;
	

	std::wstring path;
	int image;

	bool active;
};

