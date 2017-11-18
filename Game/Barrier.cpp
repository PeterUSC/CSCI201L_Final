#include "Barrier.h"
#include "Collision.h"
#include "Game.h"


Barrier::Barrier(Game* game):Character(game)
{
	Collision* coll = new Collision(this);
	this->SetCollision(coll);
	coll->setSize(32.0f, 32.0f);
	game->AddBarrier(this);
}


Barrier::~Barrier()
{
	GetGame()->RemoveBarrier(this);
}
