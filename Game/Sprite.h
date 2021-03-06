#pragma once
#include "SDL/SDL.h"
class Sprite
{
public:
	Sprite(class Character* c, int draw = 100);
	~Sprite();
	void SetTexture(SDL_Texture* text);
	void DrawTexture(SDL_Renderer* renderer);

	int GetWidth() { return width; }
	int GetHeight() { return height; }

	int GetDrawOrder() { return drawOrder; }
private:
	SDL_Texture* texture;
	class Character* owner;
	int drawOrder;
	int width;
	int height;
};

