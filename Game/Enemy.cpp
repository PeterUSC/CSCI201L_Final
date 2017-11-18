#include "Enemy.h"
#include "Game.h"
#include "Sprite.h"
#include "Collision.h"
#include "Player.h"
#include "Barrier.h"


Enemy::Enemy(Game* game):Person(game)
{
	Sprite* playerSprite = new Sprite(this, 100);
	this->SetSprite(playerSprite);
	playerSprite->SetTexture(game->GetTexture("Assets/Run1.png"));
	game->enemies.emplace_back(this);
	xSpeed = -100;
}


Enemy::~Enemy()
{
	GetGame()->RemoveEnemy(this);
}

void Enemy::Update(float deltaTime)
{
	if (directionCounter >= 5)
	{
		xSpeed *= -1;
		directionCounter = 0;
	}
	auto barriers = GetGame()->barriers;
	for (size_t i = 0; i < barriers.size(); i++)
	{
		if (barriers[i]->GetCollision()->Collide(this->GetCollision()))
		{
			xSpeed *= -1;
		}
	}
	Person::Update(deltaTime);
	if (this->GetCollision()->Collide(GetGame()->GetPlayer()->GetCollision()))
	{
		GetGame()->GetPlayer()->SetPosition(GetGame()->GetPlayer()->GetStart());
	}
	directionCounter += deltaTime;
}
