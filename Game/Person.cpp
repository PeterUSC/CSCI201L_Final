#include "Person.h"
#include "Game.h"
#include "Sprite.h"



Person::Person(Game* game)
	:Character(game)
{
	xSpeed = 0;
	ySpeed = 0;
}


Person::~Person()
{
}

void Person::ProcessInput(const Uint8 *state)
{
	Character::ProcessInput(state);
}
void Person::Update(float deltaTime)
{
	Character::Update(deltaTime);
	Vector2 newPos = GetPosition();
	newPos.x += xSpeed*deltaTime;
	ySpeed += deltaTime*Gravity;
	newPos.y += ySpeed*deltaTime;

	if (newPos.y + getSprite()->GetHeight() / 2 >= 768)
	{
		ySpeed = 0;
		newPos.y = 768 - getSprite()->GetHeight() / 2;
	}

	SetPosition(newPos);
}
