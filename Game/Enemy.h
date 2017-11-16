#pragma once
#include "Person.h"
class Enemy :
	public Person
{
public:
	Enemy(class Game* game);
	~Enemy();
	void Update(float deltaTime) override;
private:
	float directionCounter;
};

