/*
	* Bullet .cpp file
	* 19012503
	* Aim of the class: Represent FireBall/Bullet game object (functions implementation).
*/

#include "Bullet.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "ObjectManager.h"

// animation frame speed macro
#define BULLET_COOLDOWN 0.05f

// Constructur
Bullet::Bullet(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY , bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:
	CollidableObject::CollidableObject(initPos, rotation, scX, scY, activated, paths)
{
	animated = true;				// fireball is animated
	animTime = BULLET_COOLDOWN;		// animation speed.
	type = ObjectType::FIRE;		

}
/// <summary>
/// Update implementation.
/// </summary>
void Bullet::Updated(float timeFrame)
{
	if (this->active) {

		// update animation 
		this->AnimUtilityUpdate(animTime, timeFrame);

		// update positon
		this->velocity.setBearing(this->rotation, 1000.0f);
		this->position += this->velocity * timeFrame;
		
		// update collision shape position if needed
		if (this->shapeExist) {
			int width = 0;
			int height = 0;
			MyDrawEngine::GetInstance()->GetDimensions(this->image, height, width);
			this->boundingRect.PlaceAt(Vector2D(this->position.XValue - width / 2 * this->scaleY, this->position.YValue - height / 2 * this->scaleY), Vector2D(this->position.XValue + width / 2 * this->scaleY, this->position.YValue + height / 2 * this->scaleY));
		}
	}
	
}

/// <summary>
/// Collision handling.
/// </summary>
/// <param name="other"> Other Collidable Object that it collides with </param>
void Bullet::ProcessCollision(std::shared_ptr<CollidableObject> other)
{
	// If it collides with any type of the zombie - deactiveate.
	if (other->GetType() == ObjectType::ZOMBIE_WEAK	 ||
		other->GetType() == ObjectType::ZOMBIE_NORMAL||
		other->GetType() == ObjectType::ZOMBIE_HARD    
		) 
	{
		if (this->active)
			this->Deactivate();
	}
}

/// <summary>
/// Returns shape.
/// </summary>
IShape2D& Bullet::GetShape()
{
	return this->boundingRect;
}

/// <summary>
/// Make bullet STRONG - deals more damage to zombies.
/// </summary>
void Bullet::MakeStrong()
{
	this->type = ObjectType::FIRE_STRONG;
	this->scaleX *= 1.3;
	this->scaleY *= 1.3;
}
