#include "Character.h"
#include "AnimMasks.h"
#include "mydrawengine.h"

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

	//int diceR = rand() % 11;
	//bool toKnock = false;
	//if (this->type == ObjectType::ZOMBIE_HARD && diceR < 3) {
	//	toKnock = true;
	//}
	//if (this->type == ObjectType::ZOMBIE_NORMAL && diceR < 6) {
	//	toKnock = true;
	//}
	//if (this->type == ObjectType::ZOMBIE_WEAK && diceR < 9) {
	//	toKnock = true;
	//}
	//if (this->type == ObjectType::SHIP) {
	//	toKnock = true;
	//}
	//
	//
	//if (toKnock) {
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
	//}
	

}

void Character::RestrictMovement(int minY, int minX, int maxY, int maxX, int maxCameraX, int minCameraX, bool trackedByCamera)
{
	if (this->position.YValue <= minY) {
		this->position.YValue = minY;
	}
	else
	if (this->position.YValue >= maxY) {
		this->position.YValue = maxY;
	}
	
	if (trackedByCamera) {
		if (this->position.XValue <= minCameraX) {
			if (this->position.XValue <= minX) {
				this->position.XValue = minX;
			}
			MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(minCameraX, 0));
		}
		else
			if (this->position.XValue >= maxCameraX) {
				if (this->position.XValue >= maxX) {
					this->position.XValue = maxX;
				}
				MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(maxCameraX, 0));
			}
			else {
				MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(position.XValue, 0));
			}
	}
	else {
		if (this->position.XValue <= minX) {
			this->position.XValue = minX;
		}
		else if(this->position.XValue >= maxX){
			this->position.XValue = maxX;
		}
	}

	
}
