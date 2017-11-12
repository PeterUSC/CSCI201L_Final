#include "Player.h"
#include "Game.h"
#include "Sprite.h"
#include "Bullet.h"


Player::Player(Game* game):Person(game)
{
}


Player::~Player()
{
}


void Player::ProcessInput(const Uint8 *state)
{
	Person::ProcessInput(state);
	if (state[SDL_SCANCODE_D])
	{
		xSpeed = 300;
		lastDirection = Right;
	}
	else if (state[SDL_SCANCODE_A])
	{
		xSpeed = -300;
		lastDirection = Left;
	}
	else if (state[SDL_SCANCODE_A] && state[SDL_SCANCODE_D])
	{
		xSpeed = 0;
	}
	else
	{
		xSpeed = 0;
	}
	if (!spacePressed && state[SDL_SCANCODE_SPACE])
	{
		if (!inTheAir)
		{
			ySpeed = -500;
			inTheAir = true;
		}
	}
	if (!shiftPressed && state[SDL_SCANCODE_LSHIFT])
	{
		if (lastDirection==Right)
		{
			Bullet* b = new Bullet(GetGame(), 1);
		}
		if (lastDirection == Left)
		{
			Bullet* b = new Bullet(GetGame(), -1);
		}
	}
	spacePressed = state[SDL_SCANCODE_SPACE];
	shiftPressed = state[SDL_SCANCODE_LSHIFT];

}
void Player::Update(float deltaTime)
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
		inTheAir = false;
	}

	SetPosition(newPos);
}
