#include "Bullet.h"
#include "Game.h"
#include "Player.h"
#include "Sprite.h"



Bullet::Bullet(Game* game,int direct):Character(game)
{
	direction = direct;
	Sprite* bulletSprite = new Sprite(this);
	bulletSprite->SetTexture(game->GetTexture("Assets/Bullet.png"));
	Vector2 startPos = GetGame()->GetPlayer()->GetPosition();
	SetPosition(startPos);
}


Bullet::~Bullet()
{
}

void Bullet::Update(float deltaTime)
{
	Vector2 newPos = GetPosition();

	newPos.x += speed*direction*deltaTime;
	SetPosition(newPos);
	/*
	if (timeAlive >= 1)
	{
		this->SetAlive(false);
	}
	*/
	this->SetAlive(false);
	timeAlive += deltaTime;
}


void Bullet::ProcessInput(const Uint8 *state)
{
	Character::ProcessInput(state);
}
