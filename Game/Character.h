#pragma once
#include <vector>
#include <SDL/SDL_stdinc.h>
#include "Math.h"

class Character
{
private:
	class Game* myGame;
	float rotation;
	Vector2 position;
	class Sprite* mySprite;
	float xSpeed=0;
	float ySpeed=0;
	float const Gravity = 980.0f;

public:
	Character(class Game* game);
	~Character();
	void ProcessInput(const Uint8 *state);
	void Update(float deltaTime);

	void SetPosition(Vector2 newPos) { position = newPos; }
	Vector2 GetPosition() { return position; }

	float GetRotation() const { return rotation; }
	void SetRotation(float rot) { rotation = rot; }
	class Game* GetGame() { return myGame; }

	void SetSprite(class Sprite*);
	Sprite* GetSprite();
};

