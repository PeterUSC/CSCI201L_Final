#include "Player.h"
#include "Game.h"
#include "Sprite.h"
#include "Brick.h"
#include "Bullet.h"
#include "Collision.h"


Player::Player(Game* game):Person(game)
{
	Sprite* playerSprite = new Sprite(this, 100);
	this->SetSprite(playerSprite);
	playerSprite->SetTexture(game->GetTexture("Assets/Idle.png"));
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
			ySpeed = -700;
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
	Person::Update(deltaTime);
	GetGame()->SetCamPos(Vector2(GetPosition().x - 512, 0));
}
