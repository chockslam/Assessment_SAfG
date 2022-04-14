/*
    * Playable Character .cpp file
    * 19012503
    * Aim of the class:		Represents a controllable (by keyboard/controller) character (contructor implementation).
*/
#include "PlayableCharacter.h"

PlayableCharacter::PlayableCharacter(Vector2D initPos,Vector2D vel, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:
	Character::Character(initPos, vel, rotation, scX, scY, activated, paths)
{
}

