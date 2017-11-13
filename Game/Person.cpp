#include "Person.h"
#include "Game.h"
#include "Sprite.h"
#include "Collision.h"
#include "Brick.h"



Person::Person(Game* game)
	:Character(game)
{
	xSpeed = 0.0f;
	ySpeed = 0.0f;

	Collision* playerColl = new Collision(this);
	playerColl->setSize(20.0f, 64.0f);
	SetCollision(playerColl);
}


Person::~Person()
{
}

void Person::ProcessInput(const Uint8 *state)
{
	Character::ProcessInput(state);
}
void Person::Update(float deltaTime)
{

	Character::Update(deltaTime);
	Vector2 newPos = GetPosition();
	newPos.x += xSpeed*deltaTime;
	newPos.y += ySpeed*deltaTime;

	if (newPos.y + getSprite()->GetHeight() / 2 >= 768)
	{
		ySpeed = 0;
		newPos.y = 768 - getSprite()->GetHeight() / 2;
		inTheAir = false;
	}
	auto bricks = GetGame()->bricks;
	for (int i = 0; i < bricks.size(); i++)
	{

		Collision* brickColl = bricks[i]->GetCollision();
		Collision* myCollision = GetCollision();
		if (myCollision->Collide(brickColl))
		{

			float dy1 = abs(brickColl->GetMin().y - myCollision->GetMax().y);
			float dy2 = abs(brickColl->GetMax().y - myCollision->GetMin().y);
			float dx1 = abs(brickColl->GetMin().x - myCollision->GetMax().x);
			float dx2 = abs(brickColl->GetMax().x - myCollision->GetMin().x);
			if (dy1 < dy2&&dy1 < dx1&&dy1 < dx2)
			{
				newPos.y -= dy1;
				ySpeed = 0;
				inTheAir = false;
			}
			else if (dy2 < dy1 &&dy2 < dx1&&dy2 < dx2)
			{
				newPos.y += dy2;
				if (ySpeed < 0)
				{
					ySpeed = 0;
				}
			}
			else if (dx2 < dy1 &&dx2 < dx1&&dx2 < dy2)
			{
				newPos.x += dx2;
			}
			else if (dx1 < dy2&&dx1 < dy1&&dx1 < dx2)
			{
				newPos.x -= dx1;
			}
		}
	}

	SetPosition(newPos);
	ySpeed += deltaTime*Gravity;
}
