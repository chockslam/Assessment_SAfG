#include "ObjectFactory.h"
#include <memory>
#include "CollidableObject.h"
#include "AnimMasks.h"
#include "Zombie.h"
#include "Hero.h"
#include "Bullet.h"
#include "PowerUp.h"
#include "HealthBar.h"
#include "StartScreen.h"
#include "EndScreen.h"
#include "DeadScreen.h"
#include "Sprite.h"
#include "ObjectManager.h"



void ObjectFactory::AddHero(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY)
{
	std::unordered_map<std::wstring, std::list<std::wstring>> anims;



	anims[IDLE] = std::list<std::wstring>{
				L"assets\\player\\idle_1.png",
				L"assets\\player\\idle_2.png",
				L"assets\\player\\idle_5.png",
				L"assets\\player\\idle_6.png",
				L"assets\\player\\idle_7.png",
	};

	anims[RUN] = std::list<std::wstring>{
			L"assets\\player\\run_1.png",
			L"assets\\player\\run_2.png",
			L"assets\\player\\run_3.png",
			L"assets\\player\\run_4.png",
			L"assets\\player\\run_5.png",
			L"assets\\player\\run_6.png",
			L"assets\\player\\run_7.png",
			L"assets\\player\\run_8.png",
	};
	anims[FALL] = std::list<std::wstring>{
			L"assets\\player\\fall_1.png",
			L"assets\\player\\fall_1.png",
			L"assets\\player\\fall_1.png",
			L"assets\\player\\fall_1.png",
			L"assets\\player\\fall_1.png",
			L"assets\\player\\fall_2.png",
			L"assets\\player\\fall_2.png",
			L"assets\\player\\fall_3.png",
			L"assets\\player\\fall_3_5.png",
			L"assets\\player\\idle_1.png",
	};
	anims[ATTACK] = std::list<std::wstring>{
			L"assets\\player\\attack_1.png",
			L"assets\\player\\attack_2.png",
			L"assets\\player\\attack_3.png",
			L"assets\\player\\attack_4.png"
	};
	anims[DEATH] = std::list<std::wstring>{
			L"assets\\player\\fall_2.png",
			L"assets\\player\\fall_2.png",
			L"assets\\player\\fall_2.png",
			L"assets\\player\\fall_3.png",
			L"assets\\player\\fall_3.png",
			L"assets\\player\\fall_3.png",
	};
	this->om->AddObject(std::move(std::make_shared<Hero>(initPos, vel, rotation, scX, scY, false, anims)));

}

void ObjectFactory::AddZombie(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, int appearance, std::wstring type)
{
	std::unordered_map<std::wstring, std::list<std::wstring>> anims;
	// IDLE ANIMATION
	anims[IDLE] = std::list<std::wstring>{
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_1.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_2.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_3.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_4.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\idle\\idle_5.png",
	};

	// RUN ANIMATION
	anims[RUN] = std::list<std::wstring>{
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_1.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_2.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_3.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_4.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_5.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_6.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\run\\run_7.png"
	};

	// FALL ANIMATION
	anims[FALL] = std::list<std::wstring>{
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_1.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\hit\\hit_2.png"
	};

	// ATTACK ANIMATION
	anims[ATTACK] = std::list<std::wstring>{
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_1.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_2.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_3.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_4.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_5.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\attack\\attack_6.png"
	};

	// DEATH ANIMATION
	anims[DEATH] = std::list<std::wstring>{
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_1.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_2.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_3.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_4.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_5.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_6.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png",
		L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\death_1\\death_7.png"
	};
	
	auto z = std::make_shared<Zombie>(initPos, vel, rotation, scX, scY, false, anims);

	auto crawlAnim = std::list<std::wstring>{
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_1.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_2.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_3.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_4.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_5.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_6.png",
			L"assets\\enemies\\z" + std::to_wstring(appearance) + L"\\crawl\\crawl_7.png"
	};

	if (type == L"Weak Zombie")
	{
		z->setLevel(rand() % 6);
	}
	if (type == L"Normal Zombie")
	{
		z->setLevel(rand() % 5 + 6);
	}
	if (type == L"Hard Zombie")
	{
		z->setLevel(rand() % 11 + 10);
	}

	if (type == L"Weak Crawler")
	{
		z->SetAnimation(RUN, crawlAnim);
		z->setLevel(rand() % 6);
	}
	if (type == L"Normal Crawler")
	{
		z->SetAnimation(RUN, crawlAnim);
		z->setLevel(rand() % 5 + 6);
	}
	if (type == L"Hard Crawler")
	{
		z->SetAnimation(RUN, crawlAnim);
		z->setLevel(rand() % 11 + 10);
	}

	this->om->AddObject(std::move(z));
}

void ObjectFactory::AddUI(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, std::wstring type)
{

	std::unordered_map<std::wstring, std::list<std::wstring>> anims;
	std::shared_ptr<GameObject> sp;

	if (type == L"Health Bar") {
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\ui\\blood_bar.png",
		};

		sp = std::make_shared<HealthBar>(initPos, rotation, scX, scY, false, anims);
	}

	if (type == L"Dead Screen") {
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\ui\\dead_skull.png",
		};
		sp = std::make_shared<DeadScreen>(initPos, rotation, scX, scY, false, anims);
	}
	if (type == L"Start Screen") {
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\ui\\zombies_screen.png",
		};
		sp = std::make_shared<StartScreen>(initPos, rotation, scX, scY, false, anims);
	}
	if (type == L"End Screen") {
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\ui\\level_complete-mini.png",
		};

		sp = std::make_shared<EndScreen>(initPos, rotation, scX, scY, false, anims);
	}
	this->om->AddObject(std::move(sp));
}

void ObjectFactory::AddSprite(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, std::wstring type)
{

	std::unordered_map<std::wstring, std::list<std::wstring>> anims;
	std::shared_ptr<Sprite> sp;

	if (type == L"Green Fog") {
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\fog\\g_fog_1.png",
				L"assets\\fog\\g_fog_2.png",
				L"assets\\fog\\g_fog_3.png",
		};
		sp = std::make_shared<Sprite>(initPos, rotation, scX, scY, false, anims);
		sp->repeatOn(true, 0.25f);
	}
	if (type == L"Blue Fog") {
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\fog\\b_fog_1.png",
				L"assets\\fog\\b_fog_2.png",
				L"assets\\fog\\b_fog_3.png",
		};
		sp = std::make_shared<Sprite>(initPos, rotation, scX, scY, false, anims);
		sp->repeatOn(true, 0.25f);
	}
	if (type == L"Yellow Fog") {
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\fog\\y_fog_1.png",
				L"assets\\fog\\y_fog_2.png",
				L"assets\\fog\\y_fog_3.png",
		};
		sp = std::make_shared<Sprite>(initPos, rotation, scX, scY, false, anims);
		sp->repeatOn(true, 0.25f);
	}
	if (type == L"Dungeon Background") {
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\backgrounds\\battleback8.png",
		};
		sp = std::make_shared<Sprite>(initPos, rotation, scX, scY, false, anims);
	}
	if (type == L"Forrest Background") {
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\backgrounds\\battleback7.png",
		};
		sp = std::make_shared<Sprite>(initPos, rotation, scX, scY, false, anims);
	}

	this->om->AddObject(std::move(sp));
}

void ObjectFactory::AddBullet(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, std::wstring type)
{
	std::unordered_map<std::wstring, std::list<std::wstring>> anims;
	std::shared_ptr<Bullet> bullet;

	if (type == L"Normal")
	{
		anims[IDLE] = std::list<std::wstring>{
				L"assets\\fire\\fire_1.png",
				L"assets\\fire\\fire_2.png",
				L"assets\\fire\\fire_3.png",
				L"assets\\fire\\fire_4.png",
				L"assets\\fire\\fire_5.png",
				L"assets\\fire\\fire_6.png",
				L"assets\\fire\\fire_7.png",
				L"assets\\fire\\fire_8.png",
				L"assets\\fire\\fire_9.png",
				L"assets\\fire\\fire_10.png",
				L"assets\\fire\\fire_11.png",
				L"assets\\fire\\fire_12.png",
				L"assets\\fire\\fire_13.png",
				L"assets\\fire\\fire_14.png",
				L"assets\\fire\\fire_15.png"
		};

	}

	bullet = std::make_shared<Bullet>(initPos, vel, rotation, scX, scY, false, anims);

	if (type == L"Strong")
	{
		bullet->SetAnimation(IDLE, std::list<std::wstring>{
				L"assets\\fire\\fire_1.png",
				L"assets\\fire\\fire_2.png",
				L"assets\\fire\\fire_3.png",
				L"assets\\fire\\fire_4.png",
				L"assets\\fire\\fire_5.png",
				L"assets\\fire\\fire_6.png",
				L"assets\\fire\\fire_7.png",
				L"assets\\fire\\fire_8.png",
				L"assets\\fire\\fire_9.png",
				L"assets\\fire\\fire_10.png",
				L"assets\\fire\\fire_8.png",
				L"assets\\fire\\fire_9.png",
				L"assets\\fire\\fire_10.png",
				L"assets\\fire\\fire_8.png",
				L"assets\\fire\\fire_9.png",
				L"assets\\fire\\fire_10.png",
				L"assets\\fire\\fire_8.png",
				L"assets\\fire\\fire_9.png",
				L"assets\\fire\\fire_10.png",
				L"assets\\fire\\fire_11.png",
				L"assets\\fire\\fire_12.png",
				L"assets\\fire\\fire_13.png",
				L"assets\\fire\\fire_14.png",
				L"assets\\fire\\fire_15.png"
		});
		bullet->MakeStrong();
	}

	this->om->AddObject(std::move(bullet));
}

void ObjectFactory::AddPowerUp(Vector2D initPos, Vector2D vel, float rotation, float scX, float scY, int appearance)
{
	std::unordered_map<std::wstring, std::list<std::wstring>> anims;
	anims[IDLE] = std::list<std::wstring>{
				L"assets\\powerup\\p" + std::to_wstring(appearance) + L"\\pu1.png",
				L"assets\\powerup\\p" + std::to_wstring(appearance) + L"\\pu2.png",
				L"assets\\powerup\\p" + std::to_wstring(appearance) + L"\\pu3.png",
				L"assets\\powerup\\p" + std::to_wstring(appearance) + L"\\pu4.png"
	};
	this->om->AddObject(std::move(std::make_shared<PowerUp>(initPos, vel, rotation, scX, scY, false, anims)));
}

void ObjectFactory::AddLevelManager()
{
	this->om->AddObject(std::move(std::make_shared<LevelManager>()));
}
