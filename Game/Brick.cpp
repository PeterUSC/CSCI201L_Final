#include "Brick.h"
#include "Game.h"
#include "Sprite.h"



Brick::Brick(Game* game):Character(game)
{
	Sprite* brickSprite = new Sprite(this);
	brickSprite->SetTexture(game->GetTexture("Assets/BlockA.png"));
	this->SetSprite(brickSprite);
}


Brick::~Brick()
{
}
