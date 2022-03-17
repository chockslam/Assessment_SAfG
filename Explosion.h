#pragma once
#include "GameObject.h"
#include <list>



class Explosion :
    public GameObject
{
public:
    Explosion(Vector2D initPos, float rotation, float sc, bool activated, std::list<std::wstring> paths);
    ~Explosion() {};
    void Updated(float timeFrame);
    IShape2D& GetShape();
    void Initialize();
private:
    float coolDownAnim;
    std::list<std::wstring> picturePaths;
    std::list<int> pictures;
    std::list<int>::iterator it;
};

