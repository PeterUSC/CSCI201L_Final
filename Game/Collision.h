#pragma once
#include <vector>
#include <SDL/SDL_stdinc.h>
#include "Math.h"
class Collision
{
public:
	Collision(class Character* o);
	~Collision();
	Vector2 GetMin();
	Vector2 GetMax();
	void setSize(float w, float h) { width = w; height = h; }
	bool Collide(Collision* other);
private:
	class Character* owner;
	float width;
	float height;
};

