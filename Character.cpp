#include "Character.h"
#include "AnimMasks.h"

Character::Character(Vector2D initPos, Vector2D velocity, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:
	CollidableObject::CollidableObject(initPos, rotation, scX, scY, activated, paths),
	knocked(false),
	attacking(false),
	knockedTimer(-1.0f),
	attackTimer(-1.0f),
	health(1.0f)
{
}

void Character::playAnimOnce(std::wstring animName, float timeFrame)
{
	if (animName == FALL) {
		if (knocked) {
			knockedTimer -= timeFrame;
			if (knockedTimer <= 0) {
				knocked = false;
				knockedTimer = anims[currentAnimation].size() * animTime;
			}
		}
	}
	if (animName == ATTACK) {
		if (attacking) {
			attackTimer -= timeFrame;
			if (attackTimer <= 0) {
				attacking = false;
				attackTimer = anims[currentAnimation].size() * animTime;
			}
		}
	}
}

void Character::knockBack(float power, float animSpeed, std::shared_ptr<GameObject> otherObj)
{

	Vector2D normal(0.5f, 0.866f);


	Vector2D acc;
	float direction = -3.1415f / 2;
	if (otherObj && (this->position - otherObj->getPos()).XValue > 0) {
		direction = -direction;
	}
	else
	if (this->scaleX < 0)
		direction = -direction;
	acc.setBearing(this->rotation + direction, this->AccPower);
	this->velocity += acc * power;
	//this->velocity = this->velocity - 2 * (this->velocity * normal) * normal;
	this->knocked = true;
	this->animTime = animSpeed;
	this->knockedTimer = anims[currentAnimation].size() * animTime;

}
