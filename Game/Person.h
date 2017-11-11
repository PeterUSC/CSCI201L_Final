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

private:
	float xSpeed = 0;
	float ySpeed = 0;
	float const Gravity = 5.0f;
};

