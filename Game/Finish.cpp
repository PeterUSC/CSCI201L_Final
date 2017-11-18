#include "Finish.h"
#include "Game.h"
#include "Sprite.h"
#include "Collision.h"

Finish::Finish(Game* game):Character(game)
{
	Sprite* brickSprite = new Sprite(this);
	brickSprite->SetTexture(game->GetTexture("Assets/BlockB.png"));
	this->SetSprite(brickSprite);

	Collision* coll = new Collision(this);
	coll->setSize(64.0f, 32.0f);
	SetCollision(coll);
}


Finish::~Finish()
{
}
