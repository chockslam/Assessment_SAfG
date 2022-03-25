#include "PlayableCharacter.h"

PlayableCharacter::PlayableCharacter(Vector2D initPos, float rotation, float scX, float scY, bool activated, std::unordered_map<std::wstring, std::list<std::wstring>> paths)
	:
	Character::Character(initPos, rotation, scX, scY, activated, paths)
{
}
