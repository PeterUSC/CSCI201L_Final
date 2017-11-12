#pragma once
#include "Person.h"
class Player :
	public Person
{
public:
	Player(class Game* game);
	~Player();
	void ProcessInput(const Uint8 *state) override;
	void Update(float deltaTime) override;
private:
	bool spacePressed=false;
	bool shiftPressed = false;
	bool inTheAir=false;
	enum direction{Left,Right};
	direction lastDirection = Right;

};

