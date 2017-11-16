#include "Enemy.h"
#include "Game.h"
#include "Sprite.h"
#include "Collision.h"
#include "Player.h"


Enemy::Enemy(Game* game):Person(game)
{
	Sprite* playerSprite = new Sprite(this, 100);
	this->SetSprite(playerSprite);
	playerSprite->SetTexture(game->GetTexture("Assets/Run1.png"));
	game->enemies.emplace_back(this);
}


Enemy::~Enemy()
{
	GetGame()->RemoveEnemy(this);
}

void Enemy::Update(float deltaTime)
{
	if (directionCounter <= 2.5)
	{
		xSpeed = -100;
	}
	else if (directionCounter > 2.5 && directionCounter <= 5)
	{
		xSpeed = 100;
	}
	else if (directionCounter > 5)
	{
		directionCounter = 0;
	}
	Person::Update(deltaTime);
	if (this->GetCollision()->Collide(GetGame()->GetPlayer()->GetCollision()))
	{
		GetGame()->GetPlayer()->SetPosition(GetGame()->GetPlayer()->GetStart());
	}
	directionCounter += deltaTime;
}
