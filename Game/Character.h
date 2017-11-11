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
	bool alive = true;

public:
	Character(class Game* game);
	~Character();
	

	void SetPosition(Vector2 newPos) { position = newPos; }
	Vector2 GetPosition() { return position; }

	Sprite* getSprite() { return mySprite; }

	float GetRotation() const { return rotation; }
	void SetRotation(float rot) { rotation = rot; }
	class Game* GetGame() { return myGame; }

	virtual void ProcessInput(const Uint8 *state);
	virtual void Update(float deltaTime);

	void SetAlive(bool newState) { alive = newState; }
	bool isAlive() { return alive; }

	void SetSprite(class Sprite*);
	Sprite* GetSprite();
	
};

