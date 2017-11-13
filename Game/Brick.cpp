#include "Brick.h"
#include "Game.h"
#include "Sprite.h"
#include "Collision.h"



Brick::Brick(Game* game):Character(game)
{
	Sprite* brickSprite = new Sprite(this);
	brickSprite->SetTexture(game->GetTexture("Assets/BlockA.png"));
	this->SetSprite(brickSprite);

	Collision* coll = new Collision(this);
	coll->setSize(64.0f, 32.0f);
	SetCollision(coll);
	game->bricks.emplace_back(this);
}


Brick::~Brick()
{
}
