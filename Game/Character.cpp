#include "Character.h"
#include "Game.h"
#include "Sprite.h"


Character::Character(Game* game):
	myGame(game),
	mySprite(nullptr),
	position(Vector2::Zero),
	rotation(0.0f)
{
	game->AddCharacter(this);
}


Character::~Character()
{
}

void Character::ProcessInput(const Uint8 *state)
{
}
void Character::Update(float deltaTime)
{

}
void Character::SetSprite(class Sprite* newSprite)
{
	mySprite = newSprite;
}
Sprite* Character::GetSprite()
{
	return mySprite;
}

