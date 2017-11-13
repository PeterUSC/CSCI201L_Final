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
	void SetStart(Vector2 s) { start = s; SetPosition(s); }
	Vector2 GetStart() { return start; }
private:
	bool spacePressed=false;
	bool shiftPressed = false;
	enum direction{Left,Right};
	Vector2 start;
	direction lastDirection = Right;

};

