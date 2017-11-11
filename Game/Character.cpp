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
	if (state[SDL_SCANCODE_D])
	{
		xSpeed=300;
	}
	else if (state[SDL_SCANCODE_A])
	{
		xSpeed =-300.0f;
	}
	else
	{
		xSpeed = 0;
	}
}
void Character::Update(float deltaTime)
{
	Vector2 newPos = position;
	newPos.x += xSpeed*deltaTime;
	ySpeed += deltaTime*Gravity;
	newPos.y += ySpeed*Gravity;

	if (newPos.y + mySprite->GetHeight() / 2 >= 768)
	{
		ySpeed = 0;
	}
}
void Character::SetSprite(class Sprite* newSprite)
{
	mySprite = newSprite;
}
Sprite* Character::GetSprite()
{
	return mySprite;
}

