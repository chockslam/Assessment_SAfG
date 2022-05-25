/*
    * Object Factory .h file
    * 19012503
    * Aim of the class:		Game Engine Related class. Made to unify the mechanism of object creation into a single class.
    * C++ Singleton implementation taken from https://stackoverflow.com/questions/1008019/c-singleton-design-pattern;
*/

#pragma once
#include <string>
#include "vector2D.h"
#include "ObjectManager.h"
class ObjectFactory
{
public:
    static ObjectFactory& getInstance()
    {
        static ObjectFactory    instance; // Guaranteed to be destroyed.
                              // Instantiated on first use.
        return instance;
    }
private:
    ObjectFactory() {}                // Constructor? (the {} brackets) are needed here.

    // C++ 11
    // =======
    // We can use the better technique of deleting the methods
    // we don't want.
public:
    ObjectFactory(ObjectFactory const&) = delete;
    void operator=(ObjectFactory const&) = delete;

    // Note: Scott Meyers mentions in his Effective Modern
    //       C++ book, that deleted functions should generally
    //       be public as it results in better error messages
    //       due to the compilers behavior to check accessibility
    //       before deleted status
public:
    void setOM(std::shared_ptr<ObjectManager> om) { this->om = om; };
    std::shared_ptr<ObjectManager> getOM() { return this->om; };
    std::shared_ptr<LevelManager> getLevelManager() { return this->om->getLevelManager(); };
    
	void AddHero(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY);
	void AddZombie(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, int appearance, std::wstring type);
	void AddUI(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, std::wstring type);
	void AddSprite(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, std::wstring type);
	void AddBullet(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, std::wstring type = L"Normal");
	void AddPowerUp(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, int appearance);
	void AddLevelManager();
private:
	std::shared_ptr<ObjectManager> om;
};

