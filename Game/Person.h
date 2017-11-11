#pragma once
#include "Character.h"
class Person :
	public Character
{
public:
	Person(class Game* game);
	~Person();
	void ProcessInput(const Uint8 *state) override;
	void Update(float deltaTime) override;

protected:
	float xSpeed;
	float ySpeed;
	float const Gravity = 900.0f;
};

