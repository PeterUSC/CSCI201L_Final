#include "Bullet.h"
#include "Game.h"
#include "Player.h"
#include "Sprite.h"
#include "Brick.h"
#include "Collision.h"
#include "Enemy.h"



Bullet::Bullet(Game* game,int direct):Character(game)
{
	direction = direct;
	Sprite* bulletSprite = new Sprite(this);
	bulletSprite->SetTexture(game->GetTexture("Assets/Bullet.png"));
	Vector2 startPos = GetGame()->GetPlayer()->GetPosition();
	SetPosition(startPos);
	SetSprite(bulletSprite);
	Collision* coll = new Collision(this);
	coll->setSize(10.0f, 10.0f);
	SetCollision(coll);
}


Bullet::~Bullet()
{
}

void Bullet::Update(float deltaTime)
{
	Vector2 newPos = GetPosition();

	newPos.x += speed*direction*deltaTime;
	SetPosition(newPos);
	
	if (timeAlive >= 1)
	{
		this->SetAlive(false);
	}
	auto bricks = GetGame()->bricks;
	for (int i = 0; i < bricks.size(); i++)
	{
		if (GetCollision()->Collide(bricks[i]->GetCollision()))
		{
			this->SetAlive(false);
		}
	}

	auto enemies = GetGame()->enemies;
	for (int i = 0; i < enemies.size(); i++)
	{
		if (GetCollision()->Collide(enemies[i]->GetCollision()))
		{
			this->SetAlive(false);
			enemies[i]->SetAlive(false);
		}

	}

	timeAlive += deltaTime;
}


void Bullet::ProcessInput(const Uint8 *state)
{
	Character::ProcessInput(state);
}
