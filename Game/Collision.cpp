#include "Collision.h"
#include "Game.h"
#include "Character.h"



Collision::Collision(Character* o)
{
	owner = o;
}


Collision::~Collision()
{
}


Vector2 Collision::GetMin()
{
	Vector2 v = owner->GetPosition();
	v.x -= width/ 2.0f;
	v.y -= height/ 2.0f;
	return v;
}

Vector2 Collision::GetMax()
{
	Vector2 v = owner->GetPosition();
	v.x += width / 2.0f;
	v.y += height / 2.0f;
	return v;
}

bool Collision::Collide(Collision* other)
{
	Vector2 min = GetMin();
	Vector2 max = GetMax();
	Vector2 otherMin = other->GetMin();
	Vector2 otherMax = other->GetMax();
	return !(max.x < otherMin.x ||max.y < otherMin.y ||otherMax.x < min.x ||otherMax.y < min.y);
}
