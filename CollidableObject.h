/*
    * Collidable Object .h file
    * 19012503
    * Aim of the class: Represents any 'Collidable' gameObject.
    * Notes :   ABSTRACT CLASS. Its extension must implement GetShape() and ProcessCollision(...) functions
	*			GetShape must return a collision shape.
*/

#pragma once
#include "GameObject.h"

class CollidableObject :
    public GameObject
{
public:
	CollidableObject(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);
	virtual void ProcessCollision(std::shared_ptr<CollidableObject> other) = 0;
	bool DoesShapeExist() const { return shapeExist; }
	virtual IShape2D& GetShape() = 0;
protected:
	bool shapeExist; // denotes whether the collision shape needs to be updated and placed.
};

