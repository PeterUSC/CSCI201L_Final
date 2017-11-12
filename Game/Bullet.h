#pragma once
#include "Character.h"
class Bullet :
	public Character
{
public:
	Bullet(class Game* game, int direct);//direction either one or negitive one
	~Bullet();
	void Update(float deltaTime) override;
	void ProcessInput(const Uint8 *state) override;
private:
	int direction;
	float timeAlive = 0;
	float const speed = 500;
};

