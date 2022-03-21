#pragma once
#include "CollidableObject.h"
#include <list>
class Bullet :
    public CollidableObject
{

public:
    Bullet(Vector2D initPos, Vector2D vel, float rotation, float sc, bool activated, std::list<std::wstring> paths);
    ~Bullet() {};
    void Updated(float timeFrame);
    void Initialize();
    void Render();
    void ProcessCollision(std::shared_ptr<CollidableObject> other);
    IShape2D& GetShape();
private:

    float coolDownAnim;
    std::list<std::wstring> picturePaths;
    std::list<int> pictures;
    std::list<int>::iterator it;

    Vector2D velocity;
    float timer = 2.0f; 
    Rectangle2D boundingRect;
};

