#pragma once
#include "PlayableCharacter.h"
#include <memory>
#include <string>

class Hero :
    public PlayableCharacter
{
public:
    Hero(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths);
    Hero(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, bool activated);
    Hero(Vector2D initPos, Vector2D vel, float rotation);
    Hero(Vector2D initPos, Vector2D vel, bool activated);
    Hero(Vector2D initPos, Vector2D vel);
    Hero(Vector2D initPos);
    IShape2D& GetShape();
    Hero();
    ~Hero();

    void Initialize();

    Vector2D getVel() const { return this->velocity; };

    void Updated(float timeFrame);
    void ProcessCollision(std::shared_ptr<CollidableObject> other);
protected:
    void control(float timeFrame, int up = DIK_W, int left = DIK_A, int down = DIK_S, int right = DIK_D, int run = DIK_LSHIFT, int shoot = DIK_SPACE);
private:

    float invincTimer;
    Circle2D boundingCircle;
    
    const float AccPower = 200.0f;

    float poweredUpTimer;


    float shootCoolDown;

    const Vector2D right = Vector2D(100.0f, 0.0f);     
    const Vector2D left = Vector2D(-100.0f, 0.0f);
    const Vector2D up = Vector2D(0.0f, 100.0f);
    const Vector2D down = Vector2D(0.0f, -9.81f);


    // facilitates varied speed of movements.
    float posOffsetPower;
};


