#include "Character.h"
#include "Game.h"
#include "Sprite.h"
#include "Collision.h"


Character::Character(Game* game):
	myGame(game),
	mySprite(nullptr),
	position(Vector2::Zero),
	rotation(0.0f),
	myCollision(nullptr)
{
	game->AddCharacter(this);
}


Character::~Character()
{
	delete mySprite;
	if (myCollision)
	{
		delete myCollision;
	}
	myGame->RemoveCharacter(this);
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

