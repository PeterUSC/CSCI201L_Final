#include "Person.h"
#include "Game.h"
#include "Sprite.h"



Person::Person(Game* game)
	:Character(game)
{
}


Person::~Person()
{
}

void Person::ProcessInput(const Uint8 *state)
{
	Character::ProcessInput(state);
	if (state[SDL_SCANCODE_D])
	{
		xSpeed = 300;
	}
	else if (state[SDL_SCANCODE_A])
	{
		xSpeed = -300.0f;
	}
	else
	{
		xSpeed = 0;
	}
}
void Person::Update(float deltaTime)
{
	Person::Update(deltaTime);
	Vector2 newPos = GetPosition();
	newPos.x += xSpeed*deltaTime;
	ySpeed += deltaTime*Gravity;
	newPos.y += ySpeed*Gravity;

	if (newPos.y + (getSprite())->GetHeight() / 2 >= 768)
	{
		ySpeed = 0;
	}

	SetPosition(newPos);
}
